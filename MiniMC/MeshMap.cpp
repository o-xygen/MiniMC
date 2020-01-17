#include "MeshMap.h"
#include "Application.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <functional>
#include "camera.h"
#include "LogicWorld.h"

MeshMap::MeshMap()
{
	Perlin perlin;
	stride = 1.f;
	// default 100*100
	size = 100;
	map = new MapAttr * [size];
	for (int x = 0; x < size; x++) {
		map[x] = new MapAttr[size];
		for (int y = 0; y < size; y++) {
			map[x][y].heights.push_back(perlin.PerlinNoise(x, y) * 5);
			map[x][y].blockID = GrassBlock;
			auto it = blockPosMap.find(map[x][y].blockID);
            vector<glm::vec3> list;
			if (it == blockPosMap.end()) {
                vector<glm::vec3> list = vector<glm::vec3>{ glm::vec3{x,map[x][y].heights[0], y} };
				it = blockPosMap.insert({ map[x][y].blockID,  list }).first;
			}
			else {
				it->second.push_back(glm::vec3{x,map[x][y].heights[0],y});
			}
            if (map[x][y].heights[0] != 0) {
                map[x][y].heights.push_back(0);
                it->second.push_back(glm::vec3{ x,0,y });
            }
		}
	}

    GameLogic::WorldControler::meshMap = this;
    GameLogic::WorldControler::initialize();
}

void MeshMap::render()
{
	Application::blockShader->setMat4("projection", camera.getProjectionMat());
	Application::blockShader->setMat4("view", camera.getViewMat());

	Application::blockShader->use();
	for (auto iter = blockPosMap.begin(); iter != blockPosMap.end(); ++iter) {
		auto modelMats = new glm::mat4[iter->second.size()];
		int amount = 0;
		Block* block = BlockMap.at(iter->first);
		for (auto pos : iter->second) {
			auto model = glm::mat4(1.f);
			model = glm::translate(model, pos);
			model = glm::scale(model, glm::vec3{ 1.f / 16, 1.f / 16, 1.f / 16 });
			modelMats[amount++] = model;
		}
		
		// todo: only regenerate when needed
		// generate VBO
		unsigned int buffer;
		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), &modelMats[0], GL_STATIC_DRAW);

		auto func = [modelMats, iter](std::map<int, vector<int>> meshes, int start, int offset) {
			for (auto mesh : meshes) {
				glBindVertexArray(mesh.first);
				// set attribute pointers for matrix (4 times vec4)
				glEnableVertexAttribArray(3);
				glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
				glEnableVertexAttribArray(4);
				glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
				glEnableVertexAttribArray(5);
				glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
				glEnableVertexAttribArray(6);
				glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

				glVertexAttribDivisor(3, 1);
				glVertexAttribDivisor(4, 1);
				glVertexAttribDivisor(5, 1);
				glVertexAttribDivisor(6, 1);

				auto textures = mesh.second;
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, textures[0]);
				Application::blockShader->setInt("diffuse_tex1", 0);
				// draw all the identical blocks

				glDrawArraysInstanced(GL_TRIANGLES, start, offset, iter->second.size());

				glBindVertexArray(0);
			}
		};

		block->delegateDraw(func);
		glDeleteBuffers(1, &buffer);
		delete[] modelMats;
	}
}
