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

#ifndef COUPLEDODETIMEDERIVATIVE_H
#define COUPLEDODETIMEDERIVATIVE_H

#include "ODETimeKernel.h"

// Forward Declaration
class CoupledODETimeDerivative;

template <>
InputParameters validParams<CoupledODETimeDerivative>();

class CoupledODETimeDerivative : public ODETimeKernel
{
public:
  CoupledODETimeDerivative(const InputParameters & parameters);

protected:
  virtual Number computeQpResidual() override;
  virtual Number computeQpJacobian() override;

  VariableNumber & _v_dot;
  VariableNumber & _dv_dot_dv;
};

#endif // ODETIMEDERIVATIVE_H
