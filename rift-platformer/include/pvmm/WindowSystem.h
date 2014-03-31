#ifdef _WIN32
#include <Windows.h>
#include "pv/types.h"
#elif __APPLE__
#elif __linux__
#endif

namespace PV
{
#ifdef _WIN32
	/**
	 * The default bits per pixel to use for an OpenGL context.
	 */
#define DEFAULT_BITS_PER_PIXEL 32

	typedef LRESULT CALLBACK windowProcessCallback(HWND winHandle, UINT message, WPARAM windowParam, LPARAM messageParam);

	/**
	 * A class for creating windows.  These windows can then be associated with OpenGL rendering contexts.
	 * TODO Still: Add support for directX.
	 */
	class Window
	{
	public:
		Window();
		/**
		* This method creates a window using the given information and then returns its status.
		* The default window process simply handles the window closing as well as changing the viewport
		* when the window size changes.
		* @param title The title to be displayed in the window.
		* @return On success, this method will return 1.
		* On fail, it will return an error code.
		*/
		WINDOW_ERRORS create(LPCWSTR title);

		/**
		* This method creates a window using the given information and then returns its status.
		* @param title The title to be displayed in the window.
		* @param callback The callback to use when updating the window.
		* @return On success, this method will return 1.
		* On fail, it will return an error code.
		*/
		WINDOW_ERRORS create(LPCWSTR title, windowProcessCallback callback);

		/**
		* This method creates a window using the given information and then returns its status.
		* @param title The title to be displayed in the window.
		* @param callback The callback to use when updating the window.
		* @param fullscreen If true, the window will be made full screen, with the width and height determining the
		* screen resolution.  If false, it will simply create the window with the selected width and height as its
		* size.
		* @return On success, this method will return 1.
		* On fail, it will return an error code.
		*/
		WINDOW_ERRORS create(LPCWSTR title, bool fullscreen, windowProcessCallback callback);

		/**
		* This method creates a window using the given information and then returns its status.
		* @param title The title to be displayed in the window.
		* @param width An unsigned integer for the width of the window.
		* @param height An unsigned integer for the height of the window.
		* @param fullscreen If true, the window will be made full screen, with the width and height determining the
		* screen resolution.  If false, it will simply create the window with the selected width and height as its
		* size.
		* @param callback The callback to use when updating the window.
		* @return On success, this method will return 1.
		* On fail, it will return an error code.
		*/
		WINDOW_ERRORS create(LPCWSTR title, unsigned int width, unsigned int height, bool fullscreen, windowProcessCallback callback);

		/**
		 * Set the window's process callback method.  This is used when doing things such as resizing
		 * the window, closing the window, etc.
		 * @param callback The function to use.
		 */
		void setWindowProcessCallback(windowProcessCallback callback);

		/**
		 * Sets whether a window is visible or not.
		 * @param visible If true, the window will be shown, otherwise it will be hidden.
		 * @return This will return 1 if it was previously visible and 0 if it was previously hidden.
		 */
		int setVisible(bool visible);
		/**
		 * This will set the window as the current focus.
		 * @return This will return 1 if the window was brougth to the foreground and 0 otherwise.
		 */
		int Focus();
		/**
		 * This will update the window's buffer.
		 */
		void Update();
		/**
		 * This will set the window to use an OpenGL drawing context.
		 * @return Returns an error if something goes wrong when setting the drawing state.
		 */
		int setWindowDrawingStateGL();
		/**
		 * Make this window the current OpenGL context for rendering to.
		 * @return Return OK if there is no error, otherwise return the error.
		 */
		int MakeCurrentGLContext();
		/**
		 * This method returns the window's handle object if it exists.
		 * @return Returns the window's handle if it exists.  Will return NULL otherwise.
		 */
		const HWND GetWindowHandle();
		/**
		 * Gets the applications instance if it exists.
		 * @return Returns the applications instance if it exists.  Will return NULL if it does not.
		 */
		const HINSTANCE GetAppInstance();
		/**
		 * Gets whether the window is active or not.
		 * @return Returns true if the window is active, false otherwise.
		 */
		const bool IsActive();
		/**
		 * Gets whether the window is fullscreen or not.
		 * @return Returns true if the window is fullscreen, false otherwise.
		 */
		const bool IsFullscreen();
		/**
		 * Sets the window to be fullscreen when the fullscreen variable is true.  It will set it
		 * to be in a window otherwise.  When switching between a window and fullscreen, it will
		 * save the previous settings for windowed if that is what it started with.  Otherwise it
		 * will use the fullscreen as the window size.
		 * @param fullscreen Set to true to make the window fullscreen, false otherwise.
		 */
		void SetFullscreen(bool fullscreen);
		/**
		 * Gets bits per pixel for the window.
		 * @return Returns an integer indicating the bits per pixel for the window.
		 */
		const int BitsPerPixel();
		/**
		 * Gets the title of the window.
		 * @return The title of the window as a 16-bit unicode string.
		 */
		const LPCWSTR Title();
		/**
		 * This will destroy the window and its associated properties.  Be careful calling this if
		 * the window is already destroyed by the user!
		 */
		void destroy();
		/**
		 * This will destroy the OpenGL context associated with this window.
		 */
		void destroyGLSystem();
	private:
		unsigned int width;
		unsigned int height;
		RECT windowRectangle;

		/**
		 * The rendering context for where to draw stuff to.
		 */
		HGLRC renderingContext;

		/**
		 * A device context for connecting the window to the graphics
		 * interface device.
		 */
		HDC deviceContext;

		/**
		 * A window handle for managing the actual window.
		 */
		HWND windowHandle;

		/**
		 * A variable for an instance of the application.
		 */
		HINSTANCE appInstance;

		/**
		 * A boolean variable indicating whether the window is active.
		 */
		bool active;

		/**
		 * A boolean variable indicating whether the window is fullscreen or not.
		 */
		bool isFullscreen;

		/**
		 * The bits per pixel for this window.
		 */
		int bitsPerPixel;

		/**
		 * An instance of the window.
		 */
		WNDCLASS windowsClass;

		/**
		 * The window's title.
		 */
		LPCWSTR title;

		/**
		 * This method creates a window using the given information.  If an error occurs, it is returned.
		 * @param title The title to be displayed in the window.
		 * @param width An unsigned integer for the width of the window.
		 * @param height An unsigned integer for the height of the window.
		 * @param fullscreen If true, the window will be made full screen, with the width and height determining the
		 * screen resolution.  If false, it will simply create the window with the selected width and height as its
		 * size.
		 * @param bitsPerPixel The bits per pixel to use for the window.
		 * @return On success, this method will return 1.
		 * On fail, it will return an error code.
		 */
		WINDOW_ERRORS create(LPCWSTR title, unsigned int width, unsigned int height, bool fullscreen, int bitsPerPixel);

		/**
		 * The default process method for the window.
		 */
		LRESULT CALLBACK process(HWND winHandle, UINT message, WPARAM windowParam, LPARAM messageParam);
	};
#elif __APPLE__
#elif __linux__
#endif
};