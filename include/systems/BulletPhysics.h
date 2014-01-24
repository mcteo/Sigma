#pragma  once

#include "IFactory.h"
#include "ISystem.h"
#include "bullet/btBulletDynamicsCommon.h"
#include "IBulletShape.h"
#include "components/PhysicsController.h"
#include "Sigma.h"
#include "components/BulletShapeCapsule.h"

class Property;
class IMoverComponent;
struct GLFPSView;

namespace Sigma {
	class BulletPhysics
		: public Sigma::IFactory, public Sigma::ISystem<IBulletShape> {
	public:
		DLL_EXPORT BulletPhysics();
		DLL_EXPORT ~BulletPhysics();
		/**
		 * \brief Starts the Simple Physics system.
		 *
		 * \return bool Returns false on startup failure.
		 */
		DLL_EXPORT bool Start();

		/**
		 * \brief Causes an update in the system based on the change in time.
		 *
		 * Updates the state of the system based off how much time has elapsed since the last update.
		 * \param[in] const float delta The change in time since the last update
		 * \return bool Returns true if we had an update interval passed.
		 */
		DLL_EXPORT bool Update(const double delta);

		DLL_EXPORT IComponent* createBulletShapeMesh(const id_t entityID, const std::vector<Property> &properties);
		DLL_EXPORT IComponent* createBulletShapeSphere(const id_t entityID, const std::vector<Property> &properties);

		std::map<std::string,FactoryFunction> getFactoryFunctions();

		DLL_EXPORT void initViewMover(GLTransform& t);
		PhysicsController* getViewMover() {
			return this->mover;
		}
	private:
		btBroadphaseInterface* broadphase;
		btDefaultCollisionConfiguration* collisionConfiguration;
		btCollisionDispatcher* dispatcher;
		btSequentialImpulseConstraintSolver* solver;
		btDiscreteDynamicsWorld* dynamicsWorld;
		PhysicsController* mover;
		BulletShapeCapsule* moverSphere;
	};
}
