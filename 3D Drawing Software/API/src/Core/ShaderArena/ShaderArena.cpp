#include "ShaderArena.h"

namespace dra {
	[[nodiscard]] ShaderArena& ShaderArena::Instance() {
		static ShaderArena instance;
		return instance;
	}

	void ShaderArena::LoadShader(std::string& name, std::string& file_path) {
		m_ShaderList[name] = std::make_shared<Shader>(file_path);
	}

	void ShaderArena::BindShader(std::string& shader_name) {
		if (m_ShaderList.contains(shader_name)) {
			m_ShaderList[shader_name]->Bind();
		}
	}

	[[nodiscard]] std::optional<std::shared_ptr<Shader>> ShaderArena::GetShader(std::string& shader_name) noexcept {
		if (m_ShaderList.contains(shader_name)) {
			return std::make_optional(m_ShaderList.at(shader_name));
		}
		return std::nullopt;
	}

	ShaderArena::ShaderArena() {

	}

	ShaderArena::~ShaderArena() {

	}
}


