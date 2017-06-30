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

#include "DirichletBC.h"

template <>
InputParameters
validParams<DirichletBC>()
{
  InputParameters p = validParams<NodalBC>();
  p.addParam<Real>("value_r", 0.0, "Value of the BC");
  p.addParam<Real>("value_i", 0.0, "Value of the BC");
  return p;
}

DirichletBC::DirichletBC(const InputParameters & parameters)
  : NodalBC(parameters), _value(getParam<Real>("value_r"), getParam<Real>("value_i"))
{
}

Number
DirichletBC::computeQpResidual()
{
	std::cout << _value << " " << getParam<Real>("value_r") << " " << getParam<Real>("value_i") << std::endl;
	  return _u[_qp] - _value;
//  return _u[_qp] - 1.0;
}
