/*
 * Project: Rayka
 * Copyright (c) 2026, Tyler Renaud
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <Rayka/Core/Core.h>

int main() {
    Rayka::Scene myScene;
    Rayka::Mesh myMesh;
    myMesh.vertices = {
        {{0.0f, 0.0f ,1.0f}, {0.5f, 1.0f}}, //Top
        {{-1.0f, 0.0f, -1.0f}, {0.0f, 0.0f}}, //Bottom-Left
        {{1.0f, 0.0f, -1.0f}, {1.0f, 0.0f}} //Bottom-Right
    };
    myMesh.indices = {0,1,2};
    std::size_t meshIndex = myScene.addMesh(myMesh);

    Rayka::Instance myInstance;
    myInstance.meshIndex = meshIndex;
    myInstance.transform = {{0.0f, 2.0f, 0.0f}, {1.0f,1.0f,1.0f}};

    myScene.addInstance(myInstance);

    Rayka::Renderer* myRenderer = new Rayka::HostRenderer();
    myRenderer->render(myScene);
}