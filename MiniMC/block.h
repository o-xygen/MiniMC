#pragma once
#include "camera.h"
#include "LoadedTexture.h"
#include "utils.h"
#include "error.h"
#include <map>
#include <string>
#include <vector>
#include "json.hpp"
#include <glm/glm.hpp>
#include "Shader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <functional>
using std::map;
using std::string;
using std::vector;
using json = nlohmann::json;
constexpr auto textureDirPrefix = "resources/textures/";
constexpr auto filenamePostfix = ".png";
using glm::vec3;
using glm::vec2;
class Block;
extern map<int, Block*> BlockMap;

class Plane {
	// plane is default to parallel to the x or y or z axis
public:
	Plane(glm::vec3 leftBottom, glm::vec3 rightTop, glm::vec2 uvLeftBottom, glm::vec2 uvRightTop, const string& direction){
		if (direction == "up" || direction == "down") {
			vertices = new float[30]{
				leftBottom.x, leftBottom.y, leftBottom.z, uvLeftBottom.x, uvLeftBottom.y,
				leftBottom.x, leftBottom.y, rightTop.z, uvRightTop.x, uvLeftBottom.y,
				rightTop.x, rightTop.y, leftBottom.z, uvLeftBottom.x, uvRightTop.y,

				rightTop.x, rightTop.y, rightTop.z, uvRightTop.x, uvRightTop.y,
				rightTop.x, rightTop.y, leftBottom.z, uvLeftBottom.x, uvRightTop.y,
				leftBottom.x, leftBottom.y, rightTop.z, uvRightTop.x, uvLeftBottom.y,
			};
		}
		else {
			vertices = new float[30]{
				leftBottom.x, leftBottom.y, leftBottom.z, uvLeftBottom.x, uvLeftBottom.y,
				rightTop.x, leftBottom.y, rightTop.z, uvRightTop.x, uvLeftBottom.y,
				leftBottom.x, rightTop.y, leftBottom.z, uvLeftBottom.x, uvRightTop.y,

				rightTop.x, leftBottom.y, rightTop.z, uvRightTop.x, uvLeftBottom.y,
				rightTop.x, rightTop.y, rightTop.z, uvRightTop.x, uvRightTop.y,
				leftBottom.x, rightTop.y, leftBottom.z, uvLeftBottom.x, uvRightTop.y,
			};
		}

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, 30*sizeof(float), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		//unbind  
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	~Plane() {
		delete[] vertices;
	}

	void addTexture(int textureID) {
		textures.push_back(textureID);
	}

	void draw(const vec3& pos, Shader * shader) {
		glBindVertexArray(VAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textures[0]);
		shader->setInt("diffuse_tex1", 0);
		glm::mat4 projection(1.f), view(1.f), model(1.f);
		projection = camera.getProjectionMat();
		view = camera.getViewMat();
		model = glm::translate(model, pos);
		model = glm::scale(model, glm::vec3{ 1.f/16, 1.f/16, 1.f/16});
		shader->setMat4("projection", projection);
		shader->setMat4("view", view);
		shader->setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}

private:
	float *vertices;
	vector<int> textures;
	GLuint VAO, VBO;
	friend Block;
};

class Block
{
public:
	using DrawCallbackType = std::function<void (map<int, vector<int>>, int, int)>;
	Block(json conf)
	{
		blockID = conf.at("blockID");
		loadTextures(conf.at("textures"));
		// generate planes
		auto elements = conf.at("elements");
		for (auto iter = elements.begin(); iter != elements.end(); ++iter) {
			auto from = iter->at("from");
			auto to = iter->at("to");
			auto faces = iter->at("faces");
			for (auto it = faces.begin(); it != faces.end(); ++it) {
				auto uv = it.value().at("uv");
				string textureName = it.value().at("texture");
				auto info = textureMap.at(textureName.substr(1));
				Plane* plane = nullptr;
				if (it.key() == "north")
					plane = new Plane(
						vec3{ from[0], from[1], from[2] },
						vec3{ to[0], to[1], from[2] },
						vec2{ uv[0] / info.width, uv[1] / info.height },
						vec2{ uv[2] / info.width, uv[3] / info.height },
						it.key()
					);
				else if (it.key() == "south") {
					plane = new Plane(
						vec3{ from[0], from[1], to[2] },
						vec3{ to[0], to[1], to[2] },
						vec2{ uv[0] / info.width, uv[1] / info.height },
						vec2{ uv[2] / info.width, uv[3] / info.height },
						it.key()
					);
				}
				else if (it.key() == "east") {
					plane = new Plane(
						vec3{ to[0], from[1], from[2] },
						vec3{ to[0], to[1], to[2] },
						vec2{ uv[0] / info.width, uv[1] / info.height },
						vec2{ uv[2] / info.width, uv[3] / info.height },
						it.key()
					);
				}
				else if (it.key() == "west") {
					plane = new Plane(
						vec3{ from[0], from[1], from[2] },
						vec3{ from[0], to[1], to[2] },
						vec2{ uv[0] / info.width, uv[1] / info.height },
						vec2{ uv[2] / info.width, uv[3] / info.height },
						it.key()
					);
				}
				else if (it.key() == "up") {
					plane = new Plane(
						vec3{ from[0], to[1], from[2] },
						vec3{ to[0], to[1], to[2] },
						vec2{ uv[0] / info.width, uv[1] / info.height },
						vec2{ uv[2] / info.width, uv[3] / info.height },
						it.key()
					);
				}
				else if (it.key() == "down") {
					plane = new Plane(
						vec3{ from[0], from[1], from[2] },
						vec3{ to[0], from[1], to[2] },
						vec2{ uv[0] / info.width, uv[1] / info.height },
						vec2{ uv[2] / info.width, uv[3] / info.height },
						it.key()
					);
				}
				plane->addTexture(info.ID);
				planes.push_back(plane);
			}
		}
	}
	int getID() {
		return blockID;
	}

	void setPos(vec3 pos) {
		globalPos = pos;
	}

	void draw(Shader* shader) {
		for (auto plane : planes) {
			plane->draw(globalPos, shader);
		}
	}

	void delegateDraw(const DrawCallbackType& func) {
		map<int, vector<int>> meshes;
		for (auto plane : planes) {
			meshes.insert({ plane->VAO, plane->textures });
		}
		func(meshes, 0, 6);
	}

private:
	void loadTextures(json textureConf) {
		for (auto iter = textureConf.begin(); iter != textureConf.end(); ++iter) {
			string v = iter.value();
			string filename = textureDirPrefix + v;
			filename += filenamePostfix;
			auto info = TextureFromFile(filename);
			if (info.ID == -1) {
				ErrorLog::logError("blockID " + std::to_string(blockID) + "loading texture failed");
				continue;
			}
			// cache
			LoadedTextures.insert({ info.ID, true });
			// construct name ID map
			textureMap.insert({ iter.key(), info });
		}
	}

	int blockID;
	vec3 globalPos;
	vector<Plane*> planes;
	map<string, textureInfo> textureMap;
};