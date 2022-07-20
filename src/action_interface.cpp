
#define NODE_NAME action_interface

#ifndef __DEBUG_MACROS__
#define __DEBUG_MACROS__

#define LOGSQUARE( str )  "[" << str << "] "
#define OUTLABEL          LOGSQUARE( NODE_NAME )
#define TLOG( msg )       ROS_INFO_STREAM( OUTLABEL << msg )
#define TWARN( msg )      ROS_WARN_STREAM( OUTLABEL << "WARNING: " << msg )
#define TERR( msg )       ROS_WARN_STREAM( OUTLABEL << "ERROR: " << msg )

#endif
#include "rosplan_action_interface/RPActionInterface.h"
#include "ros/ros.h"

#include <string>
#include <map>
#include <signal.h>


// TODO node name!
class myaction : RPActionInterface
{
public:
	
	// node constructor
	myaction( ) : RPActionInterface( )
	{
		// init nodo

	}
	
	// action dispatch callback 
	bool concreteCallback (const rosplan_dispatch_msgs::ActionDispatch::ConstPtr& msg )
	{
		/*
		// action name
		std::cout << "action name: " << msg->name << std::endl;
		
		//params
		std::cout << "action params: " << std::endl;
		for( auto it = msg->parameters.begin() ; it != msg->parameters.end() ; ++it )
			std::cout << "param name:'" << it->key << "' value:'" << it->value << "'" << std::endl;
		*/

		if( class_initialized && ( msg->name == action_name ) )
		{
			// prendi il nome dell'azione
			// e scegli quale funzione avviare a seconda del nome
			if( action_name == "gather_hint" )
				return gather_hint_action();

			else if( action_name == "move_to_wp" )
				return move_to_wp_action();

			else if( action_name == "shift_gripper")
				return shift_gripper_action();

			else if( action_name == "reach_temple")
				return reach_temple_action();
			
			else if( action_name == "leave_temple")
				return reach_temple_action();

			else if( action_name == "check_consistent_hypo")
				return check_consistent_hypo_action();

			else
				TERR("An error occoured while looking for any correspondance with the available actions ")
				return false;
		}
		else if (!class_initialized)
		{
			// istanzia le interfacce ROS a seconda del nome dell'azione
			if( msg->name == "gather_hint" )
				gather_int_setup();

			else if( msg->name == "move_to_wp" )
				move_to_wp_setup();

			else if(msg->name == "shift_gripper")
				shift_gripper_setup();

			else if(msg->name == "reach_temple")
				reach_temple_setup();

			else if(msg->name == "leave_temple")
				leave_temple_setup();

			else if(msg->name == "check_consistent_hypo")
				check_consistent_hypo_setup();

			else if(msg->name == "query_hypo")
				query_hypo_setup();
			else
				return false;
			
			class_initialized = true;
			action_name = msg->name;

			return true;
		}
		else
			return false; // gestisci meglio il caso d'errore 
	}

private:

	// SETUP of single actions 

	bool class_initialized = false;

	std::string action_name = "";

	void gather_hint_setup()
	{
		// istanzia il subscriber con l'oracolo
		
	}

	void move_to_wp_setup()
	{
		// interfaccia con go_to_point (servizio)
		// create servicee client with ...
	}

	void reach_temple_setup()
	{
		// interfaccia con go_to_point (servizio)
		// create servicee client with ...
	}

	void leave_temple_setup()
	{
		// interfaccia con go_to_point (servizio)
		// create servicee client with ...
	}

	void check_conistent_hypo_setup()
	{
		// interfaccia con go_to_point (servizio)
		// create servicee client with ...
	}

	void query_hypo_setup()
	{
		// interfaccia con go_to_point (servizio)
		// create servicee client with ...
	}




	// ACTIONS implementation

	bool gather_hint_action()
	{
		return true; // implementazione dell'azione
	}

	bool move_to_wp_action()
	{

		return true; // chiamata a servizio go_to_point
	}

	bool leave_temple_action()
	{
		return true; // chiamata a servizio go_to_point
	}

	bool reach_temple_action()
	{
		return true; // chiamata a servizio go_to_point
	}

	bool check_consistent_hypo_action()
	{
		return true; // chiamata a servizio go_to_point
	}

	bool query_hypo_action()
	{
		return true; // chiamata a servizio go_to_point
	}



	void cbk_gather_hint( const msgtype::ConstPtr& hint )
	{
		// implementazione del subscriber ... 
	}
};


int main(int argc, char **argv) 
{
	ros::init(argc, argv, NODE_NAME, ros::init_options::AnonymousName);
	ros::NodeHandle nh("~");
	
	// create PDDL action publisher
	myaction ac( nh );
	
	// run the node
	ac.runActionInterface();
	
	return 0;
}