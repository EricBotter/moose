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

#ifndef KERNEL_H
#define KERNEL_H

#include "KernelBase.h"

class Kernel;

template <>
InputParameters validParams<Kernel>();

class Kernel : public KernelBase
{
public:
  Kernel(const InputParameters & parameters);

  virtual void computeResidual() override;
  virtual void computeJacobian() override;
  virtual void computeOffDiagJacobian(unsigned int jvar) override;
  virtual void computeOffDiagJacobianScalar(unsigned int jvar) override;

protected:
  /// Compute this Kernel's contribution to the residual at the current quadrature point
  virtual Number computeQpResidual() = 0;

  /// Compute this Kernel's contribution to the Jacobian at the current quadrature point
  virtual Number computeQpJacobian();

  /// This is the virtual that derived classes should override for computing an off-diagonal Jacobian component.
  virtual Number computeQpOffDiagJacobian(unsigned int jvar);

  /// Following methods are used for Kernels that need to perform a per-element calculation
  virtual void precalculateResidual();
  virtual void precalculateJacobian() {}
  virtual void precalculateOffDiagJacobian(unsigned int /* jvar */) {}

  /// Holds the solution at current quadrature points
  const VariableNumber & _u;

  /// Holds the solution gradient at the current quadrature points
  const VariableNumberGradient & _grad_u;

  /// Time derivative of u
  const VariableNumber & _u_dot;

  /// Derivative of u_dot with respect to u
  const VariableNumber & _du_dot_du;
};

#endif /* KERNEL_H */
