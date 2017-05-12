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

#ifndef MOOSEVARIABLESCALAR_H
#define MOOSEVARIABLESCALAR_H

#include "MooseVariableBase.h"

// libMesh forward declarations
namespace libMesh
{
template <typename T>
class NumericVector;
}

/**
 * Class for scalar variables (they are different).
 */
class MooseVariableScalar : public MooseVariableBase
{
public:
  MooseVariableScalar(unsigned int var_num,
                      const FEType & fe_type,
                      SystemBase & sys,
                      Assembly & assembly,
                      Moose::VarKindType var_kind);
  virtual ~MooseVariableScalar();

  void reinit();

  virtual bool isNodal() const override;

  //
  VariableNumber & sln() { return _u; }
  VariableNumber & slnOld() { return _u_old; }
  VariableNumber & slnOlder() { return _u_older; }

  VariableNumber & uDot() { return _u_dot; }
  VariableNumber & duDotDu() { return _du_dot_du; }

  /**
   * Set the nodal value for this variable (to keep everything up to date
   */
  void setValue(unsigned int i, Number value);

  /**
   * Set all of the values of this scalar variable to the same value
   */
  void setValues(Number value);

  void insert(NumericVector<Number> & soln);

protected:
  /// The value of scalar variable
  VariableNumber _u;
  /// The old value of scalar variable
  VariableNumber _u_old;
  /// The older value of scalar variable
  VariableNumber _u_older;

  VariableNumber _u_dot;
  VariableNumber _du_dot_du;
};

#endif /* MOOSEVARIABLESCALAR_H */
