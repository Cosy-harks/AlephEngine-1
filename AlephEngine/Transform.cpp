#include "Transform.h"
#include <gmtl/Generate.h>
#include <gmtl/EulerAngle.h>
#include <gmtl/QuatOps.h>
#include <gmtl/VecOps.h>
using namespace AlephEngine;

Transform::Transform( Entity* entity )
	: Component( entity, Component::Type<Transform>() ), scale( 1.f ), isUpdated( false ), parent( NULL ) { }

gmtl::Matrix<float, 4, 4> Transform::GetTransfromMatrix()
{
	if( !isUpdated )
	{
		transformMatrix = 

			gmtl::makeTrans<gmtl::Matrix<float, 4, 4>>( position ) *
			gmtl::makeRot<gmtl::Matrix<float, 4, 4>>( rotation ) *
			gmtl::makeScale<gmtl::Matrix<float, 4, 4>>( scale );

		isUpdated = true;
	}

	return transformMatrix;
}

void Transform::SetScale( float newScale )
{
	scale = newScale;
	isUpdated = false;
}

void Transform::Scale( float factor )
{
	scale *= factor;
	isUpdated = false;
}

void Transform::SetPosition( const gmtl::Vec<float, 3>& newPosition )
{
	position = newPosition;

	isUpdated = false;
}

void Transform::SetPosition( const float& x, const float& y, const float& z)
{
	position[0] = x;
	position[1] = y;
	position[2] = z;

	isUpdated = false;
}

void Transform::Move( const gmtl::Vec<float, 3>& dPosition )
{
	Move( dPosition[0], dPosition[1], dPosition[2] );

	isUpdated = false;
}

void Transform::Move( const float& dx, const float& dy, const float& dz)
{
	position[0] += dx;
	position[1] += dy;
	position[2] += dz;

	isUpdated = false;
}

void Transform::SetRotation( const gmtl::Quat<float>& newRotation )
{
	rotation = newRotation;

	isUpdated = false;
}

void Transform::SetRotation( const float& x, const float& y, const float& z)
{
	gmtl::setRot( rotation, gmtl::EulerAngle<float, gmtl::XYZ>( x, y, z ) );

	isUpdated = false;
}

void Transform::Rotate( const gmtl::Quat<float>& dRotation )
{
	rotation *= dRotation;

	isUpdated = false;
}
void Transform::Rotate( const float& dx, const float& dy, const float& dz )
{
	gmtl::Quat<float> dRotation;
	gmtl::setRot( dRotation, gmtl::EulerAngle<float, gmtl::XYZ>( dx, dy, dz ) );

	Rotate( dRotation );

	isUpdated = false;
}

void Transform::SetAsParent( Transform* newParent )
{

	if( parent != NULL )
	{
		parent->children.remove( this );
	}

	parent = newParent;
	newParent->children.push_back( this );
}

void Transform::SetAsChild( Transform* newChild )
{
	children.push_back( newChild );

	if( newChild->parent != NULL )
	{
		newChild->parent->children.remove( newChild );
	}

	newChild->parent = this;
}