//
// Created by grishka on 18/12/2025.
//

//
//    Copyright 2025 grish-ka
//
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//
//        http://www.apache.org/licenses/LICENSE-2.0
//
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.
//

#pragma once
#include <string>
#include <memory>

// 1. The Base Node: Every part of Lumina is a 'Node'
class ASTNode {
public:
    virtual ~ASTNode() = default;
};

// 2. Expression Node: For things that have a value (like 50)
class NumberExpr : public ASTNode {
public:
    std::string value;
    NumberExpr(std::string v) : value(v) {}
};

// 3. Statement Node: For actions (like let x = 50)
class VarDeclStmt : public ASTNode {
public:
    std::string name;
    std::unique_ptr<ASTNode> initializer; // This points to a NumberExpr
    VarDeclStmt(std::string n, std::unique_ptr<ASTNode> init)
        : name(n), initializer(std::move(init)) {}
};