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

// Interface for the optimizers.
//
// Usage example of an optimizer:
//
// AbstractOptimizer* optimizer = ...;
// while(true) {
//   GenericHyperParameters candidate;
//   auto status = optimizer->NextCandidate(&candidate);
//   if(status==kExplorationIsDone){
//     // No more parameters to evaluate.
//     break;
//   } else if(status==kWaitForEvaluation){
//     // The optimizer expected at least one evaluation result before
//     generating a new candidate. In this example, the candidates are evaluated
//     one-by-one sequentially. At this point in the code, there are no pending
//     evaluation running, so this message is not possible.
//     LOG(FATAL) << "Should not append. As no evaluation pending.";
//   }
//   double evaluation = Evaluate(candidate);
//   optimizer->ConsumeEvaluation(candidate,evaluation);
//   }
// }
// GenericHyperParameters best_params;
// double best_score;
// tie(best_params, best_score) = optimizer.BestParameters();
//
// The goal is always to MAXIMIZE the score.
//
// An optimizer is not (unless specified otherwise in specific implementations)
// thread safe.

#ifndef YGGDRASIL_DECISION_FORESTS_LEARNER_HYPERPARAMETERS_OPTIMIZER_OPTIMIZER_INTERFACE_H_
#define YGGDRASIL_DECISION_FORESTS_LEARNER_HYPERPARAMETERS_OPTIMIZER_OPTIMIZER_INTERFACE_H_

#include "yggdrasil_decision_forests/learner/abstract_learner.pb.h"
#include "yggdrasil_decision_forests/learner/hyperparameters_optimizer/hyperparameters_optimizer.pb.h"
#include "yggdrasil_decision_forests/utils/registration.h"

namespace yggdrasil_decision_forests {
namespace model {
namespace hyperparameters_optimizer_v2 {

// Status result of "AbstractOptimizer::NextCandidate()" method.
enum class NextCandidateStatus {
  // The exploration is done. No new candidate will be generated and no new
  // evaluation is expected.
  kExplorationIsDone,
  // The optimizer waits for existing evaluation results before proposing a new
  // candidate or before ending the exploration. Only possible if at least
  // one evaluation result is pending.
  kWaitForEvaluation,
  // A new candidate was generated in "candidate".
  kNewCandidateAvailable,
};

class OptimizerInterface {
 public:
  OptimizerInterface(const proto::Optimizer& config,
                     const model::proto::HyperParameterSpace& space) {}
  virtual ~OptimizerInterface() {}

  // Queries a new candidate hyperparameter set. "candidate" is only populated
  // if the returned value is "kNewCandidateAvailable".
  virtual utils::StatusOr<NextCandidateStatus> NextCandidate(
      model::proto::GenericHyperParameters* candidate) = 0;

  // Consumes a result previously generated by the last "NextCandidate" call.
  // A Nan value indicates that the evaluation failed i.e. the hyper-parameter
  // is not valid.
  virtual absl::Status ConsumeEvaluation(
      const model::proto::GenericHyperParameters& candidate, double score) = 0;

  // Returns the best parameters found so far. Can be called at any moment.
  virtual std::pair<model::proto::GenericHyperParameters, double>
  BestParameters() = 0;

  // Total expected number of candidates to evaluate before the exploration is
  // done. This value is non-contractual and can change.
  virtual int NumExpectedRounds() = 0;
};

REGISTRATION_CREATE_POOL(OptimizerInterface, const proto::Optimizer&,
                         const model::proto::HyperParameterSpace&);

#define REGISTER_AbstractHyperParametersOptimizer(implementation, key) \
  REGISTRATION_REGISTER_CLASS(implementation, key, OptimizerInterface);

}  // namespace hyperparameters_optimizer_v2
}  // namespace model
}  // namespace yggdrasil_decision_forests

#endif  // THIRD_PARTY_YGGDRASIL_DECISION_FORESTS_LEARNER_HYPERPARAMETER_OPTIMIZER_OPTIMIZER_INTERFACE_H_
