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

#ifndef NODALPROXYMAXVALUE_H
#define NODALPROXYMAXVALUE_H

#include "NodalVariablePostprocessor.h"

// Forward Declarations
class NodalProxyMaxValue;

template <>
InputParameters validParams<NodalProxyMaxValue>();

/**
 * Computes the max value at a node and broadcasts it to all
 * processors.
 */
class NodalProxyMaxValue : public NodalVariablePostprocessor
{
public:
  NodalProxyMaxValue(const InputParameters & parameters);

  virtual void initialize() override;
  virtual void execute() override;
  virtual Number getValue() override;

  /**
   * The method called to compute the value that will be returned
   * by the proxy value.
   */
  virtual Number computeValue();

  void threadJoin(const UserObject & y) override;

protected:
  Number _value;
  dof_id_type _node_id;
};

#endif // NODALPROXYMAXVALUE_H
