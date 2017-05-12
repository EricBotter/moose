/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#ifndef NEIGHBORCOUPLEABLE_H
#define NEIGHBORCOUPLEABLE_H

#include "MooseVariableBase.h"
#include "Coupleable.h"

/**
 * Enhances Coupleable interface to also couple the values from neighbor elements
 *
 */
class NeighborCoupleable : public Coupleable
{
public:
  /**
   * Constructing the object
   * @param parameters Parameters that come from constructing the object
   * @param nodal true if we need to couple with nodal values, otherwise false
   */
  NeighborCoupleable(const MooseObject * moose_object, bool nodal, bool neighbor_nodal);

  virtual ~NeighborCoupleable();

  // neighbor
  virtual const VariableNumber & coupledNeighborValue(const std::string & var_name,
                                                     unsigned int comp = 0);
  virtual const VariableNumber & coupledNeighborValueOld(const std::string & var_name,
                                                        unsigned int comp = 0);
  virtual const VariableNumber & coupledNeighborValueOlder(const std::string & var_name,
                                                          unsigned int comp = 0);

  virtual const VariableNumberGradient & coupledNeighborGradient(const std::string & var_name,
                                                           unsigned int comp = 0);
  virtual const VariableNumberGradient & coupledNeighborGradientOld(const std::string & var_name,
                                                              unsigned int comp = 0);
  virtual const VariableNumberGradient & coupledNeighborGradientOlder(const std::string & var_name,
                                                                unsigned int comp = 0);

  virtual const VariableNumberSecond & coupledNeighborSecond(const std::string & var_name,
                                                       unsigned int i = 0);

protected:
  bool _neighbor_nodal;
};

#endif /* NEIGHBORCOUPLEABLE_H */
