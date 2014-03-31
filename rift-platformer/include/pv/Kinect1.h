#ifdef _WIN32
#ifndef _KINECT1_H_
#define _KINECT1_H_

#ifndef EXCLUDE_KINECT1
#include <Windows.h>
#include <NuiApi.h>
#include <NuiImageCamera.h>
#include <NuiSensor.h>
namespace PV
{
	/**
	 * An enum for the possible errors that can occur when setting up a Microsoft Kinect for Windows.
	 */
	typedef enum
	{
		/*
		 * NotDetected occurs when a Kinect for Windows is not present for the computer to use.
		 */
		NotDetected = 0,
		/*
		 * NotEnoughBandwidth occurs when a Kinect for Windows does not have enough bandwidth on the USB port
		 * to be used.  This is usually caused by more than one Kinect for Windows being connected at once.
		 */
		 NotEnoughBandwidth = 0,
		 /*
		  * Ready occurs when a Kinect for Windows is present for the computer to use.
		  */
		  Ready = 1
	}KinectStatus;

	/**
	 * A class for connecting to and obtaining data from a Microsoft Kinect for Windows Version 1 sensor.  Using this class, you can
	 * obtain data for the skeletal features of a person, as well as the depth and color images seen by the sensor itself.
	 */
	class Kinect1
	{
	public:
		/**
		 * The default constructor for a Microsoft Kinect for Windows V1 sensor.  It will attempt to connect to the sensor with an index
		 * of 0.
		 */
		Kinect1();
		/**
		 * The default constructor for a Microsoft Kinect for Windows V1 sensor.  It will attempt to connect to the sensor with the
		 * specefied index.
		 *
		 * @param index The index of the Kinect for Windows V1 sensor to use.
		 */
		Kinect1(int index);

		/**
		 * Initializes a sensor with a chosen index.  This can be used if a Kinect for Windows V1 sensor is not detected at the program's
		 * initial launching.
		 *
		 * @param index The index of the sensor to initialize.
		 */
		KinectStatus InitializeSensor(int index);

		/**
		 * Returns the Kinect for Windows V1 status.
		 *
		 * @return Returns the status for this sensor using the KinectStatus enum.
		 */
		const KinectStatus Status() const;

		/**
		 * Destroys this instance of the Kinect for Windows V1 sensor, disconnecting it and releasing its data.
		 */
		~Kinect1();
	protected:
		/**
		 * A pointer to the actual sensor itself.  This is not exposed publically for safety reasons within this class.
		 */
		INuiSensor* sensor;
		/**
		 * The status of the Kinect for Windows V1 sensor currently.
		 */
		KinectStatus status;
	};
};
#endif

#endif

#endif
