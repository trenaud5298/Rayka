// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2026, Tyler Renaud

// Rayka Includes
#include <Rayka/Core/Scene/Scene.h>
#include <Rayka/Core/Scene/Mesh.h>

// C++ Includes
#include <iostream>

namespace Rayka {

Scene::Scene() {
    std::cout << "Scene created" << std::endl;
}

std::size_t Scene::addMesh(const Mesh& mesh) {
    std::cout << "Scene::addMesh()" << std::endl;
    m_meshes.push_back(mesh);
    return m_meshes.size() - 1;
}
const Mesh& Scene::getMesh(std::size_t index) const {
    std::cout << "Scene::getMesh()" << std::endl;
    return m_meshes.at(index);
}

const std::vector<Mesh>& Scene::getMeshes() const {
    std::cout << "Scene::getMeshes()" << std::endl;
    return m_meshes;
}

std::size_t Scene::addInstance(const Instance& instance) {
    std::cout << "Scene::addInstance()" << std::endl;
    m_instances.push_back(instance);
    return m_instances.size() - 1;
}

const Instance& Scene::getInstance(std::size_t index) const {
    std::cout << "Scene::getInstance()" << std::endl;
    return m_instances.at(index);
}

const std::vector<Instance>& Scene::getInstances() const {
    std::cout << "Scene::getInstances()" << std::endl;
    return m_instances;
}

};