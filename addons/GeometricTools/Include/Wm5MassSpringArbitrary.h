// Geometric Tools, LLC
// Copyright (c) 1998-2011
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 5.0.1 (2010/10/01)

#ifndef WM5MASSSPRINGARBITRARY_H
#define WM5MASSSPRINGARBITRARY_H

#include "Wm5PhysicsLIB.h"
#include "Wm5ParticleSystem.h"

namespace Wm5
{

template <class Real, class TVector>
class WM5_PHYSICS_ITEM MassSpringArbitrary
    : public ParticleSystem<Real,TVector>
{
public:
    // Construction and destruction.  This class represents a set of M
    // masses that are connected by S springs with arbitrary topology.  The
    // function SetSpring(...) should be called for each spring that you
    // want in the system.
    MassSpringArbitrary (int numParticles, int numSprings, Real step);
    virtual ~MassSpringArbitrary ();

    int GetNumSprings () const;
    void SetSpring (int spring, int particle0, int particle1,
        Real constant, Real length);
    void GetSpring (int spring, int& particle0, int& particle1,
        Real& constant, Real& length) const;

    Real& Constant (int spring);
    Real& Length (int spring);

    // Callback for acceleration (ODE solver uses x" = F/m) applied to
    // particle i.  The positions and velocities are not necessarily
    // m_akPosition and m_akVelocity since the ODE solver evaluates the
    // impulse function at intermediate positions.
    virtual TVector Acceleration (int i, Real time,
        const TVector* positions, const TVector* velocities);

    // The default external force is zero.  Derive a class from this one to
    // provide nonzero external forces such as gravity, wind, friction,
    // and so on.  This function is called by Acceleration(...) to append the
    // acceleration F/m generated by the external force F.
    virtual TVector ExternalAcceleration (int i, Real time,
        const TVector* positions, const TVector* velocities);

protected:
    using ParticleSystem<Real,TVector>::mNumParticles;
    using ParticleSystem<Real,TVector>::mInvMasses;

    class Spring
    {
    public:
        int Particle0, Particle1;
        Real Constant, Length;
    };

    int mNumSprings;
    Spring* mSprings;

    // Each particle has an associated array of spring indices for those
    // springs adjacent to the particle.  The set elements are spring
    // indices, not indices of adjacent particles.
    std::set<int>* mAdjacent;
};

typedef MassSpringArbitrary<float,Vector2f> MassSpringArbitrary2f;
typedef MassSpringArbitrary<double,Vector2d> MassSpringArbitrary2d;
typedef MassSpringArbitrary<float,Vector3f> MassSpringArbitrary3f;
typedef MassSpringArbitrary<double,Vector3d> MassSpringArbitrary3d;

}

#endif
