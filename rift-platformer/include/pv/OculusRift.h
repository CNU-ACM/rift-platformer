#ifndef _OCULUS_RIFT_H_
#define _OCULUS_RIFT_H_

#include "pv/types.h"
#include "pv/Matrices.h"

namespace PV
{
	/**
	 * Checks to see if there is an Oculus Rift available.
	 */
	bool DetectDevice();

	/**
	 * A class for managing any Oculus Rift devices connected to the computer.  This structure can be used
	 * to get various properties of the Oculus Rift, such as the head rotation, as well as to warp the output
	 * to be displayed in OpenGL.  DirectX support is still under construction as of now.
	 */
	class OculusRift
	{
	public:
		/**
		 * This constructor will automatically attempt to initialize and setup an
		 * Oculus Rift device that is connected to the computer.  Use the IsConnected
		 * method to see if the device was successfully setup.  You can also specify to create
		 * a virtual Oculus Rift device if the hardware is not found.  This is useful for testing the output
		 * from the device.
		 * @param useDemoRift This will tell the class to create a virtual Oculus Rift when true.
		 */
		OculusRift(bool useDemoRift);
		/**
		 * This method goes through and connect to the Oculus Rift hardware.  It then retrieves
		 * the sensor, as well as a sensor fusion, both of which can be used to retrieve data
		 * from the Oculus Rift.
		 */
		void Initialize();
		/**
		 * This method goes through and sets up the user's data for the Oculus Rift headset.
		 * This data includes things such as the interpupillary distance, field of view, and more.
		 */
		void Setup();

		/**
		 * This method checks to see if the Oculus Rift is connected and returns
		 * a boolean indicating whether it is or not.
		 * @return Returns true if the Oculus Rift is connected, false otherwise.
		 */
		const bool isConnected() const;

		/**
		 * This method updates data recieved from the Oculus Rift.  It currently pulls the change in
		 * orientation and updates the rotation of where the user is looking.
		 */
		void Update();

		/**
		* Store the view's shifted values in a 4x4 matrix of floats.
		* @param eye The eye to shift the view for (Left or Right).
		* @param projectionMatrix The projection view's offset matrix.
		* @param viewMatrix The main view's offset matrix.
		*/
		void ShiftView(RiftEye eye, float projectionMatrix[16], float viewMatrix[16]);

		/**
		 * Updates the uniforms for the shaders for the specified eye.  This can be usedto create custom shaders that
		 * warp the view for the Oculus Rift, though we recommend that you check that you are doing so correctly, as
		 * this can affect the user's experience if done improperly.
		 * @param eye The eye to setup the shaders for (Left or Right).
		 * @param program The program that the shader is attached to.
		 */
		void UpdateUniforms(RiftEye eye, unsigned int program);

		/**
		* This function sets up the vertex and fragment shaders for the barrel distortion on the Oculus Rift.
		* It will create a program object and compile and link predefined shaders to it.  This can then be used
		* for rendering the scene with an Oculus Rift.
		* @param program Stores the program's ID.
		* @param fragment Stores the fragment shader's ID.
		* @param vertex Stores the vertex shader's ID.
		*/
		void SetupShaders(int &program, int &fragment, int &vertex);

		/**
		* This function sets up the vertex and fragment shaders for the barrel distortion on the Oculus Rift.
		* It will create a program object and compile and link the chosen shaders to it.  This can then be used
		* for rendering the scene with an Oculus Rift.  If NULL is passed to either the vertex shader or fragment
		* shader name, then it will use the default shader that is provided with Project Virtua (default.vs and default.fs).
		* @param vertexShader The name of the vertex shader file to load.
		* @param fragmentShader The name of the fragment shader file to load.
		* @param program Stores the program's ID.
		* @param fragment Stores the fragment shader's ID.
		* @param vertex Stores the vertex shader's ID.
		*/
		void SetupShaders(const char* vertexShader, const char* fragmentShader, int &program, int &fragment, int &vertex);

		/**
		 * Get the rotation values for the angle of rotation for where the user is looking.
		 * This is in Euler angles.
		 * @return The rotation on the X, Y, and Z axis in Euler angles.
		 */
		const rotation_t GetRotation() const;

		/**
		 * Get viewport for the Oculus Rift.  This should be split in half for each eye.
		 * @return The viewport of what the Oculus Rift can see.
		 */
		const OVR::Util::Render::Viewport GetViewport() const;

		/**
		 * Compose the final rendered image that the Rift should see per eye using textured quads.
		 * @param leftEyeTexture The image that the left eye should see.
		 * @param rightEyeTexture The image that the right eye should see.
		 */
		void ComposeFinalImage(unsigned int leftEyeTexture, unsigned int rightEyeTexture);

		/**
		* The center viewing point.
		*/
		float ViewCenter;
		/**
		* The offset for the projection view due to the eyes and screen size.
		*/
		float ProjectionCenterOffset;
		/**
		* This is half of the interpupillary distance (IE: Distance between the eyes).
		*/
		float HalfIPD;

		/**
		* The field of view on the Y-axis that can be seen by the camera.
		*/
		float FieldOfView;
		/**
		* The aspect ration to display with the camera.
		*/
		float AspectRatio;

		/**
		 * This is the deconstructor for he Oculus Rift device.  This method will automatically
		 * cleanup all resources associated with the Oculus Rift device.
		 */
		~OculusRift();
	protected:
		/**
		  * Manages the USB devices connected to the computer.
		  */
		OVR::Ptr<OVR::DeviceManager> deviceManager;
		/**
		  * Manages a Head Mounted Display (HMD) device (IE: The oculus rift).  This is used
		  * mainly for getting hardware information rather than user info (IE: No eye distance info).
		  */
		OVR::Ptr<OVR::HMDDevice> HMDHardwareDevice;
		/**
		  * The actual oculus rift sensor.  Can be used to get various things from the actual
		  * device once created.
		  */
		OVR::Ptr<OVR::SensorDevice> Sensor;
		/**
		  * The oculus rift's information in the form of a Head Mounted Display (HMD).  This is used
		  * to get information specially needed for HMD's, rather than hardware information.
		  */
		OVR::HMDInfo HMD;
		/**
		  * The fusion sensor object is used to get information from the HDM's built in sensors.
		  * (IE: Accelerometer information, orientation, etc.)
		  */
		OVR::SensorFusion* sensorFusion;

		/**
		  * A boolean indicating whether an oculus rift is connected or not.
		  */
		bool connected;

		/**
		* A boolean indicating whether the connected Rift is a virtual one or not. (IE: Hardware or emulated)
		*/
		bool virtuallyConnected;

		/**
		  * The orientation of the oculus rift. (yaw, pitch, roll)
		  */
		orientation_t Orientation;
		/**
		  * The orientation of the oculus rift. (Quaternion)
		  */
		orientation_quart_t Orientation_quart;
		/**
		  * The previous orientation of the oculus rift. (yaw, pitch, roll) This is used to
		  * update the orientation data properly.
		  */
		orientation_t OldOrientation;
		/**
		  * The previous orientation of the oculus rift. (Quaternion) This is used to
		  * update the orientation data properly.
		  */
		orientation_quart_t OldOrientation_quart;

		/**
		  * The configuration for the stereo-scopic viewing.  Contains properties like how big
		  * the display for each eye is.
		  */
		OVR::Util::Render::StereoConfig StereoConfiguration;
		/**
		  * The stereo parameters for the left eye.
		  */
		OVR::Util::Render::StereoEyeParams LeftEye;
		/**
		  * The stereo parameters for the right eye.
		  */
		OVR::Util::Render::StereoEyeParams RightEye;
		/**
		 * The viewport for what the user's eyes can see.
		 */
		OVR::Util::Render::Viewport viewport;

		/**
		* This is the program handle that is used for the shaders associated with each eye.
		*/
		int defaultProgram;
		/**
		* This is the shader handle for the vertex shader.
		*/
		int vertexShader;
		/**
		 * This is the shader handle for the fragment shader.
		 */
		int fragmentShader;

		/**
		 * The rotation data for where the user is looking.
		 */
		rotation_t Rotation;

		/**
		 * This is the vertex array object handle used to render the quad.
		 */
		unsigned int quadVAOHandle;
		/**
		* This is the vertex buffer object handle used to render the quad.
		*/
		unsigned int quadVBOHandle;
		/**
		* This is the color buffer object handle used to render the quad.
		*/
		unsigned int quadCBOHandle;
		/**
		* This is the texture coordinates buffer object handle used to render the quad.
		*/
		unsigned int quadTCBOHandle;

		/**
		 * This function initializes the quad that is used for rendering the final scene to the eyes of the Oculus Rift.
		 */
		void InitializeRenderQuad();

		/**
		 * Renders to the screen for the Oculus Rift's eyes using OpenGL.  This is the compatiblity version
		 * to be used on OpenGL versions less than 2.0.
		 * @param eye The eye to render for.
		 */
		void renderGLBelow2(RiftEye eye);
	};
};
#endif