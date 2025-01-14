/*
 * Copyright 2022 Google LLC.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @fileoverview Internal and external definitions.
 * @externs
 */

/**
 * Structure of the InputFeature defined in "inference.cc".
 *
 * @typedef {{
 *   name: string,
 *   type: string,
 *   internalIdx: number,
 * }}
 */
let InputFeature;

/**
 * Structure of the vector of InputFeature defined in "inference.cc".
 *
 * @typedef {{
 *   size: function(): number,
 *   get: function(number) : !InputFeature,
 * }}
 */
let InternalInputFeatures;

/**
 * Structure of the vector of float defined in "inference.cc".
 *
 * @typedef {{
 *   size: function(): number,
 *   get: function(number) : number,
 * }}
 */
let InternalPredictions;

/**
 * Structure of the InternalModel defined in "inference.cc".
 *
 * @typedef {{
 *   predict: function(): !InternalPredictions,
 *   newBatchOfExamples: function(number),
 *   setNumerical: function(number,number,number),
 *   setCategoricalInt: function(number,number,number),
 *   setCategoricalString: function(number,number,string),
 *   setCategoricalSetString: function(number,number,!Array<string>),
 *   getInputFeatures: function(): !InternalInputFeatures,
 *   delete: function(),
 * }}
 */
let InternalModel;


/**
 * emscripten generated module.
 *
 * @typedef {{
 *    FS : {
 *      mkdirTree: function(string),
 *      writeFile: function(string, ?, ?),
 *      readdir: function(string),
 *      unlink: function(string),
 *      rmdir: function(string),
 *      }
 * }}
 */
let Module;

/**
 * JSZip utility.
 *
 * See https://stuk.github.io/jszip/documentation/api_jszip/for_each.html
 *
 * @typedef {{
 *   loadAsync: function(string),
 * }}
 */
let JSZip;
