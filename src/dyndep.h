// Copyright 2015 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef NINJA_DYNDEP_LOADER_H_
#define NINJA_DYNDEP_LOADER_H_

#include <map>
#include <string>
#include <vector>
using namespace std;

struct DiskInterface;
struct Edge;
struct Node;
struct State;

/// Store dynamically-discovered dependency information for one edge.
struct Dyndeps {
  Dyndeps(): used_(false), restat_(false) {}
  bool used_;
  bool restat_;
  vector<Node*> implicit_inputs_;
  vector<Node*> implicit_outputs_;
};

/// Store data loaded from one dyndep file.  Map from an edge
/// to its dynamically-discovered dependency information.
struct DyndepFile: public map<Edge*, Dyndeps> {};

/// DyndepLoader loads dynamically discovered dependencies, as
/// referenced via the "dyndep" attribute in build files.
struct DyndepLoader {
  DyndepLoader(State* state, DiskInterface* disk_interface)
      : state_(state), disk_interface_(disk_interface) {}

  bool LoadDyndeps(Node* node, string* err) const;
  bool LoadDyndeps(Node* node, DyndepFile* ddf, string* err) const;

 private:
  bool LoadDyndepFile(Node* file, DyndepFile* ddf, string* err) const;

  bool UpdateEdge(Edge* edge, Dyndeps const* dyndeps, string* err) const;

  State* state_;
  DiskInterface* disk_interface_;
};

#endif  // NINJA_DYNDEP_LOADER_H_
