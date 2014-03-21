/*
* Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

/* 
 * Base code for CS 296 Software Systems Lab 
 * Department of Computer Science and Engineering, IIT Bombay
 * Instructor: Parag Chaudhuri
 */

/*
*\struct to document a C-struct.
*\union to document a union.
*\enum to document an enumeration type.
*\fn to document a function.
*\var to document a variable or typedef or enum value.
*\def to document a #define.
*\typedef to document a type definition.
*\file to document a file.
*\namespace to document a namespace.
*\package to document a Java package.
*\interface to document an IDL interface.
*/

#include "cs296_base.hpp"
#include "render.hpp"

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include "GL/freeglut.h"
#endif

#include <cstring>
using namespace std;

#include "dominos.hpp"

namespace cs296
{
  /*!  This is the constructor 
   * This is the documentation block for the constructor.
   */ 
  
  dominos_t::dominos_t()
  {
	 /*! \section sec Elements of Graphics
	 * 	
	 */ 
    //Ground
    
    /*! \subsection Ground
     * 
     * \brief Ground is the base of all the elements and wedge. All other static elements are in rest with 
     * respect to it.
     * 
     * \li b1 is pointer of \a b2Body type, set to an edge shape using b2EdgeShape which is set to a line between 
     * point (-90,0) and (90,0).
     * 
     * \li \a bd is \a b2BodyDef type which stores the data about ground and then creates it.
     * \n \n
     */
     
    b2Body* b1;
    { 
      b2EdgeShape shape; 
      shape.Set(b2Vec2(-90.0f, 0.0f), b2Vec2(90.0f, 0.0f));
      b2BodyDef bd;
      b1 = m_world->CreateBody(&bd); 
      b1->CreateFixture(&shape, 0.0f);
    }
     
          
    //Top horizontal shelf
    {
	
	/*! \subsection sub_shelf Top horizontal shelf
	 * 
	 * \brief The shelf supports dominos and is fixed at some height below the pendulum.
	 * 
	 * \li \a Shape is \a b2PolygonShape. \a b2PolygonShape gives box shape.
	 *  It set to an Box shape using \a setAsBox function with length 12 units and width 0.5 unit, which is set to a position 
	 * (-31, 30) on the Cartesian plane of frame.
	 * 
	 * \li \a bd is \a b2BodyDef type variable used to define shelf and stores the data about it till we create it.
	 * \n \n
	 */
	
      b2PolygonShape shape;
      shape.SetAsBox(6.0f, 0.25f);
	
      b2BodyDef bd;
      bd.position.Set(-31.0f, 30.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
    
	/*! \subsection sub_dominos Dominos
	 * 
	 * \brief These are simply array of 10 blocks built using predefined shape \b Box, they are dynamic objects and can topple and move 
	 * over the shelf and fall off the edge. Coefficient of friction is set to 0.1 and density of each individual dominos is 20 (in proper units).
	 * 
	 * \li \a Shape is \a b2PolygonShape. \a b2PolygonShape gives box shape.
	 *  It is set to a Box shape using \a setAsBox function with dimension .2 unit X 2 unit, which is set to a position at 
	 * (-35.5 + i, 31.25), where i = 0, 1...9. 
	 * 
	 * \li \a bd is \a b2BodyDef type variable used to define the dominos and stores the data about it till we create this.
	 * \n \n
	 */
	 
    //Dominos
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 1.0f);
	
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 20.0f;
      fd.friction = 0.1f;
		
      for (int i = 0; i < 10; ++i)
	{
	  b2BodyDef bd;
	  bd.type = b2_dynamicBody;
	  bd.position.Set(-35.5f + 1.0f * i, 31.25f);
	  b2Body* body = m_world->CreateBody(&bd);
	  body->CreateFixture(&fd);
	}
    }
      
    //Another horizontal shelf
    /*! \subsection sub_shelf2 Another horizontal shelf
     * 
     * \brief It is the shelf having balls on it.
     * 
     *  \li \a Shape is \a b2PolygonShape. \a b2PolygonShape gives box shape.
	 *  It is set to a Box shape using \a setAsBox function with length 14 units and width 0.5 unit, which is set to a position 
	 * (-21, 20) on the Cartesian plane of frame.
	 * 
	 * \li \a bd is \a b2BodyDef type variable used to define the shelf, and stores the data about it until we create it.
	 * \n \n
     * 
     */
    {
      b2PolygonShape shape;
      shape.SetAsBox(7.0f, 0.25f, b2Vec2(-20.f,20.f), 0.0f);
	
      b2BodyDef bd;
      bd.position.Set(1.0f, 6.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }


    //The pendulum that knocks the dominos off
    
    /*! \subsection pend Pendulum
     * 
     * \li \b Vertical \b rod : It is supporting rod to which pendulum is hinged. b2 is a pointer to class \a b2Body.
     * Its dimensions are set to 0.5 unit X 3 unit, using shape object, which is of a data type \a b2PolygonShape.
     * Its position is set to (-36.5, 28), using function \a position.Set() on \a bd. \a bd is \a b2BodyDef type variable
     * used to define shelf and stores the data about it until we create it.
     * 
     * \li \b Bob : It is a tiny ball which is the moving part of significance. b4 is a pointer to class \a b2Body. 
     * Its dimensions are set to 0.5 unit X 0.5 unit, using shape object, which is of a data type \a b2PolygonShape.
     * Its position is set to (-40, 33), using function \a position.Set on bd. bd is \a b2BodyDef type variable
     * used to define shelf and stores the data about it until we create it.
     * 
     * \li \b Joint : jd is an object of data-type \a b2RevoluteJointDef, which joins objects together. 
     * \n \n
     */
     
    {
      b2Body* b2;
      {
	b2PolygonShape shape;
	shape.SetAsBox(0.25f, 1.5f);
	  
	b2BodyDef bd;
	bd.position.Set(-36.5f, 28.0f);
	b2 = m_world->CreateBody(&bd);
	b2->CreateFixture(&shape, 10.0f);
      }
	
      b2Body* b4;
      {
	b2PolygonShape shape;
	shape.SetAsBox(0.25f, 0.25f);
	  
	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position.Set(-40.0f, 33.0f);
	b4 = m_world->CreateBody(&bd);
	b4->CreateFixture(&shape, 2.0f);
      }
	
      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(-37.0f, 40.0f);
      jd.Initialize(b2, b4, anchor);
      m_world->CreateJoint(&jd);
    }
      
    /*! \subsection balls Train of balls
     * 
     * \brief They are the train of dynamic balls on shelf which transfer movement from dominos to the pulley. For each ball:
     * 
     * \li \a Spherebody is the pointer of data type \a b2Body. Its shape is assigned to circle using circle variable of data type
     * \a b2CircleShape. Its radius is assigned to 0.5. \li \a ballfd is an object of class \a b2FixtureDef, which stores 
     * information about the circle. Density of the ball is 1 unit. It is frictionless and perfectly inelastic.
     * 
     *\brief The balls are placed at (-22.2 +i, 26.6), where i = 0..9, using function \a position.Set(), on \a ballbd.
     * \li \a ballbd is \a b2BodyDef type which stores the data about the ball and then creates it.
     * \n \n
     */
     
     
    //The train of small spheres
    {
      b2Body* spherebody;
	
      b2CircleShape circle;
      circle.m_radius = 0.5;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 1.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
	
      for (int i = 0; i < 10; ++i)
	{
	  b2BodyDef ballbd;
	  ballbd.type = b2_dynamicBody;
	  ballbd.position.Set(-22.2f + i*1.0, 26.6f);
	  spherebody = m_world->CreateBody(&ballbd);
	  spherebody->CreateFixture(&ballfd);
	}
    }

	/*! \subsection pulley Pulley-System
	 * 
	 * \brief Pulley is a system of rope and bucket which changes the direction of force applied, so when balls fall into
	 * the bucket and it descends, the shelf on the other side of pulley rises. 
	 * \a bd is a pointer of data type \a b2BodyDef , whose position is set to (-10, 15), using function \a position.Set() on \a bd.
	 * It consists of various components:
	 * 
	 * \li \b Open \b Box :  It is to hold the balls which fall off the higher shelf, so that the weight of the balls in the bucket increases
	 *  enough to lift the other side.
	 * \a fd1, \a fd2 and \a fd3 are pointers of type \a b2FixtureDef while \a bs1, \a bs2 and \a bs3 are objects of class \a b2PolygonShape,
	 *  which is used to assign shape to \a fd1, \a fd2 and \a fd3 respectively.
	 *  All of these walls have length 4 and thickness 0.4, density = 10, friction = 0.5 and coefficient of restitution = 0.
	 * 
	 * \li \b Bar : position of \a bd is set using function \a position.Set() to (-10, 15), and its type is set to \a b2_dynamicBody,
	 *  so that it can move.
	 * 
	 * \li \b pulley \b joint : \a myjoint is pointer of data type \a b2PulleyJointDef. \a worldAnchorOnBody1, \a worldAnchorOnBody2,
	 * \a worldAnchorOnGround1 and \a worldAnchorOnGround2 are all objects of data type \a b2Vec2, initialised by (-10,15), (10, 15),
	 *  (-10, 20) and (10,20), which denotes the position of various joints.
	 * \b Float \b ratio : It's the ratio ..... . For our simulation it is 1.
	 * 
	 * \n \n
	 */
	 
    //The pulley system
    {
      b2BodyDef *bd = new b2BodyDef;
      bd->type = b2_dynamicBody;
      bd->position.Set(-10,15);
      bd->fixedRotation = true;

      
      //The open box
      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 10.0;
      fd1->friction = 0.5;
      fd1->restitution = 0.f;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(2,0.2, b2Vec2(0.f,-1.9f), 0);
      fd1->shape = &bs1;
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 10.0;
      fd2->friction = 0.5;
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(0.2,2, b2Vec2(2.0f,0.f), 0);
      fd2->shape = &bs2;
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 10.0;
      fd3->friction = 0.5;
      fd3->restitution = 0.f;
      fd3->shape = new b2PolygonShape;
      b2PolygonShape bs3;
      bs3.SetAsBox(0.2,2, b2Vec2(-2.0f,0.f), 0);
      fd3->shape = &bs3;
       
      b2Body* box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd1);
      box1->CreateFixture(fd2);
      box1->CreateFixture(fd3);

      //The bar
      bd->position.Set(10,15);	
      fd1->density = 34.0;	  
      b2Body* box2 = m_world->CreateBody(bd);
      box2->CreateFixture(fd1);

      // The pulley joint
      b2PulleyJointDef* myjoint = new b2PulleyJointDef();
      b2Vec2 worldAnchorOnBody1(-10, 15); // Anchor point on body 1 in world axis
      b2Vec2 worldAnchorOnBody2(10, 15); // Anchor point on body 2 in world axis
      b2Vec2 worldAnchorGround1(-10, 20); // Anchor point for ground 1 in world axis
      b2Vec2 worldAnchorGround2(10, 20); // Anchor point for ground 2 in world axis
      float32 ratio = 1.0f; // Define ratio
      myjoint->Initialize(box1, box2, worldAnchorGround1, worldAnchorGround2, box1->GetWorldCenter(), box2->GetWorldCenter(), ratio);
      m_world->CreateJoint(myjoint);
    }
    
    /*! \subsection rev_plate Revolving horizontal platform
     * \a bd is \a b2BodyDef type which stores the data about ground and then creates it.
     * It consists of two components:
     *  
     * \li \b Plateform: Its shape is set to Box of dimensions 4.4 units X 0.4 unit using function \a SetAsBox(). 
     * \a bd is \a b2BodyDef type which stores the data about revolving horizontal platform then creates it. It is a dynamic body.
     *  Its position is set to (14, 14) using function \a position.Set().
     * 
     * \li \b Hinge: It is the centre of rotation about which the platform rotates. Its shape is set to Box of dimensions 0.4 units
     *  X 0.4 unit using function \a SetAsBox(). 
     * \a bd is \a b2BodyDef type which stores the data about revolving horizontal platform then creates it. It is a dynamic body.
     *  Its position is set to (14, 16).
     * 
     * Joining of these two components is done using object \a jointDef, which is an instantiation of \a b2RevoluteJointDef. It is used to make joints about which bodies can rotate.
     * The joint objects here are not allowed to collide so the value of \a jointDef.collideConnected is set to false.
     * \n \n
     */
     
    
    //The revolving horizontal platform
    {
      b2PolygonShape shape;
      shape.SetAsBox(2.2f, 0.2f);
	
      b2BodyDef bd;
      bd.position.Set(14.0f, 14.0f);
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 1.f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd);

      b2PolygonShape shape2;
      shape2.SetAsBox(0.2f, 2.0f);
      b2BodyDef bd2;
      bd2.position.Set(14.0f, 16.0f);
      b2Body* body2 = m_world->CreateBody(&bd2);

      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);
    }


    //The heavy sphere on the platform
    
    /*! \subsection heavy_s Heavy sphere on the platform
     * 
     * \li \a sbody is a pointer of data type \a b2Body. Its shape is set to circle using \a b2CircleShape. Its radius is 1 unit.
     * 
     * \li \a ballfd is an object of class \a b2FixtureDef. Its density is set to 50, friction to 0, and is perfectly inelastic.
     * Its position is set to (14, 18) using the function \a .position.Set() on \a ballbd.
     * 
     * \li \a bd is \a b2BodyDef type which stores the data about ground and then creates it.
     * \n \n
     */
     
     
    {
      b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = 1.0;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 50.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(14.0f, 18.0f);
      sbody = m_world->CreateBody(&ballbd);
      sbody->CreateFixture(&ballfd);
    }

	


    //The see-saw system at the bottom
    
    
    /*! \subsection tri Triangle wedge
     * 
     * \li \a wedgebd is \a b2BodyDef type which stores the data about see-saw and then creates it.
     * \li \a sbody is an array of type \a b2Body. \a poly is an object of class \a b2PolygonShape. It has 3 vertices,
     *  position of which is set to (-1,0)(1,0)(0,1.5) by calling function \a set on each vertex.
     * Its density is 10. It is frictionless and perfectly inelastic. Position of \a wedgebd is set to (30, 0) using function \a position.set().
     * \n \n
     * 
     */
     
     
    {
      //The triangle wedge
      b2Body* sbody;
      b2PolygonShape poly;
      b2Vec2 vertices[3];
      vertices[0].Set(-1,0);
      vertices[1].Set(1,0);
      vertices[2].Set(0,1.5);
      poly.Set(vertices, 3);
      b2FixtureDef wedgefd;
      wedgefd.shape = &poly;
      wedgefd.density = 10.0f;
      wedgefd.friction = 0.0f;
      wedgefd.restitution = 0.0f;
      b2BodyDef wedgebd;
      wedgebd.position.Set(30.0f, 0.0f);
      sbody = m_world->CreateBody(&wedgebd);
      sbody->CreateFixture(&wedgefd);
      
      

      //The plank on top of the wedge
      
      /*! \subsection plank Plank on the top of wedge
       * 
       * \li \a bd2 is \a b2BodyDef type which stores the data about the plank and then creates it.
       * Its dimensions are set to 30 unit X 0.4 unit, using shape object, which is of a data type \a b2PolygonShape and function \a SetAsBox.
	   * Its position is set to (30, 1.5), using function \a position.Set() on \a bd2. Its density is set to 1. 
       * \n \n
       */
       
       
       
      b2PolygonShape shape;
      shape.SetAsBox(15.0f, 0.2f);
      b2BodyDef bd2;
      bd2.position.Set(30.0f, 1.5f);
      bd2.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd2);
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 1.f;
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape;
      body->CreateFixture(fd2);

      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(30.0f, 1.5f);
      jd.Initialize(sbody, body, anchor);
      m_world->CreateJoint(&jd);

      //The light box on the right side of the see-saw
      /*! \subsection box Light box
       * 
       * \li \a bd3 is \a b2BodyDef type which stores the data about Light Box and then creates it.
       * Its dimensions are set to 4 unit X 4 unit, using \a shape2 object, which is of a data type \a b2PolygonShape and function \a SetAsBox.
	   * Its position is set to (40, 2), using function \a position.Set() on \a bd2. Its density is set to 0.01. 
       * \n \n
       */
      
      b2PolygonShape shape2;
      shape2.SetAsBox(2.0f, 2.0f);
      b2BodyDef bd3;
      bd3.position.Set(40.0f, 2.0f);
      bd3.type = b2_dynamicBody;
      b2Body* body3 = m_world->CreateBody(&bd3);
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 0.01f;
      fd3->shape = new b2PolygonShape;
      fd3->shape = &shape2;
      body3->CreateFixture(fd3);
    }
     /*! \section us Objects created by us
     */
    //Shelf holding the new sphere
    /*! \subsection p1 Plank with a sphere collision with square box.
     * 
     * \li \b a \b fixed \b plank
     * \li \b ball: It finally collides with square box.
     */
     
    {
      b2PolygonShape shape;
      shape.SetAsBox(3.0f, 0.25f);
	  //shape.SetAsBox(7.0f, 0.25f, b2Vec2(-20.f,20.f), 0.0f);
      b2BodyDef bd;
      bd.position.Set(30.0f, 11.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
     
    //The new sphere
    {
      b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = 0.6;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 1.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.5f;
      b2BodyDef ballbd_new;
      ballbd_new.type = b2_dynamicBody;
      ballbd_new.position.Set(28.7f, 11.4f);
      sbody = m_world->CreateBody(&ballbd_new);
      sbody->CreateFixture(&ballfd);
    }
    
    	//The another horizontal platform
    /*! \subsection p2 A ball on rotating rod 
     * 
     * \li \b Rotating \b rod: Rod initially at horizontal and with ball placed at center.
     * \li \b ball: The ball comes from top and collides with the system and rod starts rotating and the center ball falls down on right on plank placed on see-saw
     * 
     */
    {
      b2PolygonShape shape;
      shape.SetAsBox(4.2f, 0.2f);
	
      b2BodyDef bd;
      bd.position.Set(17.0f, 9.0f);
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 1.f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd);

      b2PolygonShape shape2;
      shape2.SetAsBox(0.2f, 2.0f);
      b2BodyDef bd2;
      bd2.position.Set(17.0f, 11.0f);
      b2Body* body2 = m_world->CreateBody(&bd2);

      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);
    }
    
    {
      b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = 1.0;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 100.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(17.0f, 13.0f);
      sbody = m_world->CreateBody(&ballbd);
      sbody->CreateFixture(&ballfd);
    }
  
  
  //rohit
  

     /*! \subsection Hinged rod and wedge collision
      *  collision provides a horizontal velocity to wedge under the momentum conservation law and as the ground has some friction, wedge moves with deceleration, until it piles down the stack of dominos
      * 
      *  \li \b Sphere: It initiates the hinge motion for the hinged rod and wedge collision.
      * \li \b revolving \b joint: Its the hinged rod initially at horizontal position, which after the collision comes in motion under the angular momentum conservation law.
      * \li \b triangular \b wedge: The revolving rod collides with the wedge to provide a constant velocity to wedge under the angular momentum conservation law.
      * \li \b dominos: A set of sticks which is collapsed by moving wedge.
      * 
      */
    // 3rd sphere
    {
      b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = 0.8;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 0.7f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.5f;
      b2BodyDef ballbd_new;
      ballbd_new.type = b2_dynamicBody;
      ballbd_new.position.Set(-24.5f, 26.5f);
      sbody = m_world->CreateBody(&ballbd_new);
      sbody->CreateFixture(&ballfd);
    }
    
    // revolving r
    {
      b2PolygonShape shape;
      shape.SetAsBox(4.2f, 0.2f);
	
      b2BodyDef bd;
      bd.position.Set(-30.0f, 5.0f);
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 1.f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd);

      b2PolygonShape shape2;
      shape2.SetAsBox(0.2f, 2.0f);
      b2BodyDef bd2;
      bd2.position.Set(-30.0f, 7.0f);
      b2Body* body2 = m_world->CreateBody(&bd2);

      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);
    }
    
    {
      //The triangle wedge at the bottom
      b2Body* sbody;
      b2PolygonShape poly;
      b2Vec2 vertices[3];
      vertices[0].Set(-3,0);
      vertices[1].Set(0,6);
      vertices[2].Set(0,0);
      poly.Set(vertices, 3);
      b2FixtureDef wedgefd;
      wedgefd.shape = &poly;
      wedgefd.density = 0.05f;
      wedgefd.friction = 0.3f;
      wedgefd.restitution = 0.0f;
      b2BodyDef wedgebd;
      wedgebd.type = b2_dynamicBody;
      wedgebd.position.Set(-28.0f, 0.5f);
      sbody = m_world->CreateBody(&wedgebd);
      sbody->CreateFixture(&wedgefd);
    }
    
    //Dominos
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.2f, 2.0f);
	
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 0.02;
      fd.friction = 0.1f;
		
      for (int i = 0; i < 5; ++i)
	{
	  b2BodyDef bd;
	  bd.type = b2_dynamicBody;
	  bd.position.Set(-12.5f + 1.5f * i, 0.5f);
	  b2Body* body = m_world->CreateBody(&bd);
	  body->CreateFixture(&fd);
	}
    }
}

  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
