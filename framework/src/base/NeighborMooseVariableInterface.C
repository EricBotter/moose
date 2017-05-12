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

#include "NeighborMooseVariableInterface.h"

// MOOSE includes
#include "Assembly.h"
#include "MooseVariable.h"
#include "MooseTypes.h"
#include "Problem.h"
#include "SubProblem.h"

NeighborMooseVariableInterface::NeighborMooseVariableInterface(const MooseObject * moose_object,
                                                               bool nodal)
  : MooseVariableInterface(moose_object, nodal)
{
}

NeighborMooseVariableInterface::~NeighborMooseVariableInterface() {}

const VariableNumber &
NeighborMooseVariableInterface::neighborValue()
{
  if (_nodal)
    return _variable->nodalSlnNeighbor();
  else
    return _variable->slnNeighbor();
}

const VariableNumber &
NeighborMooseVariableInterface::neighborValueOld()
{
  if (_nodal)
    return _variable->nodalSlnOldNeighbor();
  else
    return _variable->slnOldNeighbor();
}

const VariableNumber &
NeighborMooseVariableInterface::neighborValueOlder()
{
  if (_nodal)
    return _variable->nodalSlnOlderNeighbor();
  else
    return _variable->slnOlderNeighbor();
}

const VariableNumberGradient &
NeighborMooseVariableInterface::neighborGradient()
{
  if (_nodal)
    mooseError("Nodal variables do not have gradients");

  return _variable->gradSlnNeighbor();
}

const VariableNumberGradient &
NeighborMooseVariableInterface::neighborGradientOld()
{
  if (_nodal)
    mooseError("Nodal variables do not have gradients");

  return _variable->gradSlnOldNeighbor();
}

const VariableNumberGradient &
NeighborMooseVariableInterface::neighborGradientOlder()
{
  if (_nodal)
    mooseError("Nodal variables do not have gradients");

  return _variable->gradSlnOlderNeighbor();
}

const VariableNumberSecond &
NeighborMooseVariableInterface::neighborSecond()
{
  if (_nodal)
    mooseError("Nodal variables do not have second derivatives");

  return _variable->secondSlnNeighbor();
}

const VariableNumberSecond &
NeighborMooseVariableInterface::neighborSecondOld()
{
  if (_nodal)
    mooseError("Nodal variables do not have second derivatives");

  return _variable->secondSlnOldNeighbor();
}

const VariableNumberSecond &
NeighborMooseVariableInterface::neighborSecondOlder()
{
  if (_nodal)
    mooseError("Nodal variables do not have second derivatives");

  return _variable->secondSlnOlderNeighbor();
}

const VariableTestSecond &
NeighborMooseVariableInterface::neighborSecondTest()
{
  if (_nodal)
    mooseError("Nodal variables do not have second derivatives");

  return _variable->secondPhiFaceNeighbor();
}

const VariablePhiSecond &
NeighborMooseVariableInterface::neighborSecondPhi()
{
  if (_nodal)
    mooseError("Nodal variables do not have second derivatives");

  return _mvi_assembly->secondPhiFaceNeighbor();
}
