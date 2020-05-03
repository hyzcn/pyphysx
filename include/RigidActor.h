/**
 * Copyright (c) CTU  - All Rights Reserved
 * Created on: 5/3/20
 *     Author: Vladimir Petrik <vladimir.petrik@cvut.cz>
 */

#ifndef PYPHYSX_RIGIDACTOR_H
#define PYPHYSX_RIGIDACTOR_H

#include <Physics.h>
#include <BasePhysxPointer.h>
#include <Shape.h>
#include <transformation_utils.h>

class RigidActor : public BasePhysxPointer<physx::PxRigidActor> {
public:
    explicit RigidActor(physx::PxRigidActor *physxPtr) : BasePhysxPointer(physxPtr) {}

    auto get_global_pose() {
        return transform_to_eigen(get_physx_ptr()->getGlobalPose());
    }

    void set_global_pose(const Eigen::Vector3f &pos, const Eigen::Vector4f &quat) {
        get_physx_ptr()->setGlobalPose(eigen_to_transform(pos, quat));
    }

    void attach_shape(const Shape &shape) {
        get_physx_ptr()->attachShape(*shape.get_physx_ptr());
    }

    auto get_atached_shapes() {
        std::vector<physx::PxShape *> shapes_ptr(get_physx_ptr()->getNbShapes());
        get_physx_ptr()->getShapes(&shapes_ptr[0], shapes_ptr.size());
        return from_vector_of_physx_ptr<Shape>(shapes_ptr);
    }
};


#endif //PYPHYSX_RIGIDACTOR_H