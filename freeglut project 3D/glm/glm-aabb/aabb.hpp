#ifndef IAUNS_GLM_AABB_HPP
#define IAUNS_GLM_AABB_HPP

#include "glm\glm.hpp"

namespace CPM_GLM_AABB_NS {

/// Standalone axis aligned bounding box implemented built on top of GLM.
class AABB
{
public:
  /// Builds a null AABB.
	AABB() {
		setNull();
	}

  /// Builds an AABB that encompasses a sphere.
  /// \param[in]  center Center of the sphere.
  /// \param[in]  radius Radius of the sphere.
	AABB(const glm::vec3& center, glm::float_t radius) {
		setNull();
		extend(center, radius);
	}

  /// Builds an AABB that contains the two points.
	AABB(const glm::vec3& p1, const glm::vec3& p2) {

		setNull();
		extend(p1);
		extend(p2);

	}

	AABB(const AABB& aabb) {
		setNull();
		extend(aabb);
  }
	~AABB() {}

  /// Set the AABB as NULL (not set).
  void setNull()      {mMin = glm::vec3(1.0); mMax = glm::vec3(-1.0);}

  /// Returns true if AABB is NULL (not set).
  bool isNull() const {return mMin.x > mMax.x || mMin.y > mMax.y || mMin.z > mMax.z;}

  /// Extend the bounding box on all sides by \p val.
  void extend(glm::float_t val) {
	  if (!isNull())
	  {
		  mMin -= glm::vec3(val);
		  mMax += glm::vec3(val);
	  }
  }

  /// Expand the AABB to include point \p p.
  void extend(const glm::vec3& p)
  {
	  if (!isNull())
	  {
		  mMin = glm::min(p, mMin);
		  mMax = glm::max(p, mMax);
	  }
	  else
	  {
		  mMin = p;
		  mMax = p;
	  }
  }

  /// Expand the AABB to include a sphere centered at \p center and of radius \p
  /// radius.
  /// \param[in]  center Center of sphere.
  /// \param[in]  radius Radius of sphere.
  void extend(const glm::vec3& p, glm::float_t radius) {
	  glm::vec3 r(radius);
	  if (!isNull())
	  {
		  mMin = glm::min(p - r, mMin);
		  mMax = glm::max(p + r, mMax);
	  }
	  else
	  {
		  mMin = p - r;
		  mMax = p + r;
	  }
  }

  /// Expand the AABB to encompass the given \p aabb.
  void extend(const AABB& aabb) {
	  if (!aabb.isNull())
	  {
		  extend(aabb.mMin);
		  extend(aabb.mMax);
	  }
  }


  /// Expand the AABB to include a disk centered at \p center, with normal \p
  /// normal, and radius \p radius.
  /// \xxx Untested -- This function is not represented in our unit tests.
  void extendDisk(const glm::vec3& c, const glm::vec3& n, glm::float_t r) {
	  if (glm::length(n) < 1.e-12) { extend(c); return; }
	  glm::vec3 norm = glm::normalize(n);
	  glm::float_t x = sqrt(1 - norm.x) * r;
	  glm::float_t y = sqrt(1 - norm.y) * r;
	  glm::float_t z = sqrt(1 - norm.z) * r;
	  extend(c + glm::vec3(x, y, z));
	  extend(c - glm::vec3(x, y, z));
  }

  /// Translates AABB by vector \p v.
  void translate(const glm::vec3& v) {
	  if (!isNull())
	  {
		  mMin += v;
		  mMax += v;
	  }
  }

  void setPos(const glm::vec3& v) {
	  if (!isNull())
	  {
		  mMin += v;
		  mMax += v;
	  }
  }

  /// Scale the AABB by \p scale, centered around \p origin.
  /// \param[in]  scale  3D vector specifying scale along each axis.
  /// \param[in]  origin Origin of scaling operation. Most useful origin would
  ///                    be the center of the AABB.
  void scale(const glm::vec3& scale, const glm::vec3& origin);

  /// Retrieves the center of the AABB.
  glm::vec3 getCenter() const {
	  if (!isNull())
	  {
		  glm::vec3 d = getDiagonal();
		  return mMin + (d * glm::float_t(0.5));
	  }
	  else
	  {
		  return glm::vec3(0.0);
	  }
  }

  /// Retrieves the diagonal vector (computed as mMax - mMin).
  /// If the AABB is NULL, then a vector of all zeros is returned.
  glm::vec3 getDiagonal() const {
	  if (!isNull())
		  return mMax - mMin;
	  else
		  return glm::vec3(0);
  }

  /// Retrieves the longest edge.
  /// If the AABB is NULL, then 0 is returned.
  glm::float_t getLongestEdge() const;

  /// Retrieves the shortest edge.
  /// If the AABB is NULL, then 0 is returned.
  glm::float_t getShortestEdge() const;

  /// Retrieves the AABB's minimum point.
  glm::vec3 getMin() const {return mMin;}

  /// Retrieves the AABB's maximum point.
  glm::vec3 getMax() const {return mMax;}

  /// Returns true if AABBs share a face overlap.
  /// \xxx Untested -- This function is not represented in our unit tests.
  bool overlaps(const AABB& bb) const {
	  if (isNull() || bb.isNull())
		  return false;

	  if (bb.mMin.x > mMax.x || bb.mMax.x < mMin.x)
		  return false;
	  else if (bb.mMin.y > mMax.y || bb.mMax.y < mMin.y)
		  return false;
	  else if (bb.mMin.z > mMax.z || bb.mMax.z < mMin.z)
		  return false;

	  return true;
  }
  bool collision(const AABB& bb, glm::vec3 & intersection) const {
	  if (isNull() || bb.isNull())
		  return false;

	  if (bb.mMin.x > mMax.x || bb.mMax.x < mMin.x)
		  return false;
	  else if (bb.mMin.y > mMax.y || bb.mMax.y < mMin.y)
		  return false;
	  else if (bb.mMin.z > mMax.z || bb.mMax.z < mMin.z)
		  return false;
	  real Amin, Bmin, Amax, Bmax;
	  AABB aux;


	  Amin = mMin.x; Amax = mMax.x;
	  Bmin = bb.mMin.x; Bmax = bb.mMax.x;
	  if (Bmin > Amin)
		  Amin = Bmin;
	  aux.mMin.x = Amin;
	  if (Bmax < Amax)
		  Amax = Bmax;
	  aux.mMax.x = Amax;
	  

	  Amin = mMin.y; Amax = mMax.y;
	  Bmin = bb.mMin.y; Bmax = bb.mMax.y;
	  if (Bmin > Amin)
		  Amin = Bmin;
	  aux.mMin.y = Amin;
	  if (Bmax < Amax)
		  Amax = Bmax;
	  aux.mMax.y = Amax;

	  Amin = mMin.z; Amax = mMax.z;
	  Bmin = bb.mMin.z; Bmax = bb.mMax.z;
	  if (Bmin > Amin)
		  Amin = Bmin;
	  aux.mMin.z= Amin;
	  if (Bmax < Amax)
		  Amax = Bmax;
	  aux.mMax.z = Amax;
	  
	  intersection = aux.getCenter();

	  return true;
  }

  /// Type returned from call to intersect.
  enum INTERSECTION_TYPE { INSIDE, INTERSECT, OUTSIDE };
  /// Returns one of the intersection types. If either of the aabbs are invalid,
  /// then OUTSIDE is returned.
  INTERSECTION_TYPE intersect(const AABB& bb) const;

  /// Function from SCIRun. Here is a summary of SCIRun's description:
  /// Returns true if the two AABB's are similar. If diff is 1.0, the two
  /// bboxes have to have about 50% overlap each for x,y,z. If diff is 0.0,
  /// they have to have 100% overlap.
  /// If either of the two AABBs is NULL, then false is returned.
  /// \xxx Untested -- This function is not represented in our unit tests.
  bool isSimilarTo(const AABB& b, glm::float_t diff = 0.5) const;

private:

  glm::vec3 mMin;   ///< Minimum point.
  glm::vec3 mMax;   ///< Maximum point.
};

} // namespace CPM_GLM_AABB_NS 

#endif 
