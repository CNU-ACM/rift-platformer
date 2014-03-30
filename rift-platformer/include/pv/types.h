#ifndef _TYPES_H_
#define _TYPES_H_

#include <OVR.h>

namespace PV
{
#ifdef _WIN32
	/**
	 * A list of potential errors when creating and destroy a window and it's parts.
	 */
	enum WINDOW_ERRORS
	{
		/**
		 * This indicates that everything was ok with creating a window.
		 */
		OK = 1,
		/**
		 * This indicates that an unhandled error occured!  If this happens, please file a bug report!
		 */
		 RANDOM_FAILURE = 0,
		 /**
		  * This indicates that the window-class could not be registered properly.
		  */
		  REGISTER_ERROR = -1,
		  /**
		   * This indicates that there was an error creating a fullscreen window.
		   */
		   FULLSCREEN_ERROR = -2,
		   /**
			* This indicates that there was an error actually creating the window.
			*/
			CREATION_ERROR = -3,
			/**
			 * This indicates there was an error releasing the device context.
			 */
			 DC_RELEASE_ERROR = -4,
			 /**
			  * This indicates that there was a problem destroying a window associated with a window handle.
			  */
			  WH_DESTROY_ERROR = -5,
			  /**
			   * This indicates that there was an error unregistering the window's class.
			   */
			   WC_UNREGISTER_ERROR = -6,
			   /**
				* This indicates that there was an error changing the OpenGL context for destroying the context.
				*/
				WDGL_CHANGE_CONTEXT_ERROR = -7,
				/**
				 * This indicates there was an error actually deleting the OpenGL context.
				 */
				 WDGL_DELETE_CONTEXT_ERROR = -8,
				 /**
				  * This indicates that there was an error getting the device context.
				  */
				  WCGL_GET_CONTEXT_ERROR = -9,
				  /**
				   * This indicates that there was an error getting the pixel format.
				   */
				   WCGL_GET_PF_ERROR = -10,
				   /**
					* This indicates that there was an error setting the pixel format.
					*/
					WCGL_SET_PF_ERROR = -11,
					/**
					 * This indicates that there was an error creating the OpenGL context.
					 */
					 WCGL_CREATE_CONTEXT_ERROR = -12,
					 /**
					  * This indicates that there was an error setting the OpenGL context.
					  */
					  WCGL_SET_CONTEXT_ERROR = -13
	};
#endif

	/**
	 * This is a structure used for storing rotation data as Eular angles.
	 * It has an X, Y, Z, and W property.
	 */
	struct rotation_t
	{
		float x;
		float y;
		float z;
		float w;
	};

	/**
	 * This is a structure used for orientation data.  The
	 * angles are stored as Eular angles.
	 */
	struct orientation_t
	{
		/**
		 * Rotation on the Y axis.
		 */
		float yaw;
		/**
		 * Rotation on the X axis.
		 */
		float pitch;
		/**
		 * Rotation on the Z axis.
		 */
		float roll;
	};

	/**
	 * This is a structure used for orientation data.  The
	 * angles are stored as Quartonian angles.
	 */
	struct orientation_quart_t
	{
		/**
		 * A vector with X, Y, and Z variables respresenting the axis as normals that
		 * is being roated around.
		 */
		OVR::Vector3f axis;
		/**
		 * The angle of rotation for this orientation.
		 */
		float angle;
	};

	/**
	 * The eyes available for the Oculus Rift.
	 */
	enum RiftEye
	{
		Left = 0,
		Right = 1
	};
};

#endif