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

#include "NodalProxyMaxValue.h"
#include "MooseMesh.h"
#include "SubProblem.h"
// libMesh
#include "libmesh/boundary_info.h"

template <>
InputParameters
validParams<NodalProxyMaxValue>()
{
  InputParameters params = validParams<NodalVariablePostprocessor>();
  return params;
}

NodalProxyMaxValue::NodalProxyMaxValue(const InputParameters & parameters)
  : NodalVariablePostprocessor(parameters), _value(-std::numeric_limits<Real>::max())
{
}

void
NodalProxyMaxValue::initialize()
{
  _value = -std::numeric_limits<Real>::max();
}

Number
NodalProxyMaxValue::computeValue()
{
  return _u[_qp];
}

void
NodalProxyMaxValue::execute()
{
  Number val = computeValue();

  if (val.real() > _value.real())
  {
    _value = val;
    _node_id = _current_node->id();
  }
}

Number
NodalProxyMaxValue::getValue()
{
  Real r = _value.real(); //FIXME - this is NOT going to work
  gatherProxyValueMax(r, _node_id);
  return _node_id;
}

void
NodalProxyMaxValue::threadJoin(const UserObject & y)
{
  const NodalProxyMaxValue & pps = static_cast<const NodalProxyMaxValue &>(y);
  if (pps._value.real() > _value.real())
  {
    _value = pps._value;
    _node_id = pps._node_id;
  }
}
