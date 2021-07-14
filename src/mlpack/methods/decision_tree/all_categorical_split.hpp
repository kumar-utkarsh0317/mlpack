/**
 * @file methods/decision_tree/all_categorical_split.hpp
 * @author Ryan Curtin
 *
 * This file defines a tree splitter that split a categorical feature into all
 * of the possible categories.
 *
 * mlpack is free software; you may redistribute it and/or modify it under the
 * terms of the 3-clause BSD license.  You should have received a copy of the
 * 3-clause BSD license along with mlpack.  If not, see
 * http://www.opensource.org/licenses/BSD-3-Clause for more information.
 */
#ifndef MLPACK_METHODS_DECISION_TREE_ALL_CATEGORICAL_SPLIT_HPP
#define MLPACK_METHODS_DECISION_TREE_ALL_CATEGORICAL_SPLIT_HPP

#include <mlpack/prereqs.hpp>

namespace mlpack {
namespace tree {

/**
 * The AllCategoricalSplit is a splitting function that will split categorical
 * features into many children: one child for each category. This is a generic
 * splitting strategy and can be used for both regression and classification
 * trees.
 *
 * @tparam FitnessFunction Fitness function to evaluate gain with.
 */
template<typename FitnessFunction>
class AllCategoricalSplit
{
 public:
  // No extra info needed for split.
  class AuxiliarySplitInfo { };

  /**
   * Check if we can split a node.  If we can split a node in a way that
   * improves on 'bestGain', then we return the improved gain.  Otherwise we
   * return the value 'bestGain'.  If a split is made, then splitInfo and
   * aux may be modified.  For this particular split type, aux will be empty
   * and splitInfo will store the number of children of the node.
   *
   * This overload is used only for classification.
   *
   * @param bestGain Best gain seen so far (we'll only split if we find gain
   *      better than this).
   * @param data The dimension of data points to check for a split in.
   * @param numCategories Number of categories in the categorical data.
   * @param labels Labels for each point.
   * @param numClasses Number of classes in the dataset.
   * @param weights Weights associated with labels.
   * @param minimumLeafSize Minimum number of points in a leaf node for
   *      splitting.
   * @param splitInfo Stores split information on a successful split.
   * @param minimumGainSplit Minimum  gain split.
   * @param aux Auxiliary split information, which may be modified on a
   *      successful split.
   */
  template<bool UseWeights, typename VecType, typename LabelsType,
           typename WeightVecType>
  static double SplitIfBetter(
      const double bestGain,
      const VecType& data,
      const size_t numCategories,
      const LabelsType& labels,
      const size_t numClasses,
      const WeightVecType& weights,
      const size_t minimumLeafSize,
      const double minimumGainSplit,
      arma::vec& splitInfo,
      AuxiliarySplitInfo& aux);

  /**
   * Check if we can split a node.  If we can split a node in a way that
   * improves on 'bestGain', then we return the improved gain.  Otherwise we
   * return the value 'bestGain'.  If a split is made, then splitInfo and
   * aux may be modified.  For this particular split type, aux will be empty
   * and splitInfo will store the number of children of the node.
   *
   * This overload is used only for regression.
   *
   * @param bestGain Best gain seen so far (we'll only split if we find gain
   *      better than this).
   * @param data The dimension of data points to check for a split in.
   * @param numCategories Number of categories in the categorical data.
   * @param responses Responses for each point.
   * @param weights Weights associated with responses.
   * @param minimumLeafSize Minimum number of points in a leaf node for
   *      splitting.
   * @param splitInfo Stores split information on a successful split.
   * @param minimumGainSplit Minimum  gain split.
   * @param aux Auxiliary split information, which may be modified on a
   *      successful split.
   */
  template<bool UseWeights, typename VecType, typename ResponsesType,
           typename WeightVecType>
  static double SplitIfBetter(
      const double bestGain,
      const VecType& data,
      const size_t numCategories,
      const ResponsesType& responses,
      const WeightVecType& weights,
      const size_t minimumLeafSize,
      const double minimumGainSplit,
      double& splitInfo,
      AuxiliarySplitInfo& aux,
      FitnessFunction fitnessFunction);

  /**
   * Return the number of children in the split.
   *
   * @param splitInfo Auxiliary information for the split.
   * @param * (aux) Auxiliary information for the split (Unused).
   */
  static size_t NumChildren(const double& splitInfo,
                            const AuxiliarySplitInfo& /* aux */);

  /**
   * Calculate the direction a point should percolate to.
   *
   * @param point the Point to use.
   * @param splitInfo Auxiliary information for the split.
   * @param * (aux) Auxiliary information for the split (Unused).
   */
  template<typename ElemType>
  static size_t CalculateDirection(
      const ElemType& point,
      const double& splitInfo,
      const AuxiliarySplitInfo& /* aux */);
};

} // namespace tree
} // namespace mlpack

// Include implementation.
#include "all_categorical_split_impl.hpp"

#endif
