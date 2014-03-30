#ifndef _MIN_OPEN_GL_H_
#define _MIN_OPEN_GL_H_

#ifdef _WIN32

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif

#include <Windows.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#define glGetProcAddress(funcname) wglGetProcAddress(funcname)

#elif __APPLE__
#define __stdcall
#include <mach-o/dyld.h>
#include <string.h>
#include <stdlib.h>
#include <OpenGL/GL.h>
#include <OpenGL/GLU.h>
inline void* glGetProcAddress(const char* name)
{
	NSSymbol symbol = NULL;
	char* symbolName;
	symbolName = malloc(strlen(name) + 2);
	strcpy(symbolName + 1, name);
	symbolName[0] = '_';

	if (NSLookupSymbolInImage(symbolName))
	{
		symbol = NSLookupSymbolInImage(symbolName);
	}
	free(symbolName);
	return symbol ? NSAddressOfSymbol(symbol) : NULL;
}

#elif __linux
#define __stdcall
#include <GL/glx.h>
#define glGetProcAddress(funcname) glXGetProcAddress((const GLubyte*)funcname)

#elif __unix
#define __stdcall

#elif __posix
#define __stdcall

#else
#define __stdcall
#include <GL/glx.h>
#define glGetProcAddress(funcname) glXGetProcAddress((const GLubyte*)funcname)
#endif

namespace PV
{
	/**
 * The define for getting the major version (X.0) in OpenGL.
 */
#define PV_GL_MAJOR_VERSION 0x821B
	/**
	 * The define for getting the minor version (0.X) in OpenGL.
	 */
#define PV_GL_MINOR_VERSION 0x821C

#define PV_GL_COMPILE_STATUS 0x8B81
#define PV_GL_LINK_STATUS 0x8B82
#define PV_GL_INFO_LOG_LENGTH 0x8B84

#define PV_GL_ARRAY_BUFFER 0x8892
#define PV_GL_ELEMENT_ARRAY_BUFFER 0x8893
#define PV_GL_STATIC_DRAW 0x88E4

	/**
	 * Specifies to the glCreateShader function to create a fragment shader.
	 */
#define PV_GL_FRAGMENT_SHADER 0x8B30
	/**
	 * Specifies to the glCreateShader function to create a vertex shader.
	 */
#define PV_GL_VERTEX_SHADER 0x8B31

#define PV_GL_TEXTURE0                       0x84C0

	/**
	 * A function pointer for the glCreateShader function.
	 */
	typedef GLuint(__stdcall* pv_glCreateShaderFunction) (GLenum shaderType);
	/**
	 * A function pointer for the glShaderSource function.
	 */
	typedef void(__stdcall* pv_glShaderSourceFunction) (GLuint shader, GLsizei count, const char* const* string, const GLint* length);
	/**
	 * A function pointer for the glCompileShader function.
	 */
	typedef void(__stdcall* pv_glCompileShaderFunction) (GLuint shader);
	/**
	 * A function pointer for the glGetShaderiv function.
	 */
	typedef void(__stdcall* pv_glGetShaderivFunction) (GLuint shader, GLenum pname, GLint* params);
	/**
	* A function pointer for the glGetShaderInfoLog function.
	*/
	typedef void(__stdcall* pv_glGetShaderInfoLogFunction) (GLuint shader, GLsizei maxLength, GLsizei* length, char* infoLog);
	/**
	 * A function pointer for the glDeleteShader function.
	 */
	typedef void(__stdcall* pv_glDeleteShaderFunction) (GLuint shader);
	/**
	 * A function pointer for the glCreateProgram function.
	 */
	typedef GLuint(__stdcall* pv_glCreateProgramFunction) (void);
	/**
	 * A function pointer for the glAttachShader function.
	 */
	typedef void(__stdcall* pv_glAttachShaderFunction) (GLuint program, GLuint shader);
	/**
	* A function pointer for the glLinkProgram function.
	*/
	typedef void(__stdcall* pv_glLinkProgramFunction) (GLuint program);
	/**
	* A function pointer for the glUseProgram function.
	*/
	typedef void(__stdcall* pv_glUseProgramFunction) (GLuint program);
	typedef void(__stdcall* pv_glGetProgramivFunction) (GLuint program, GLenum pname, GLint* pararms);
	typedef void(__stdcall* pv_glGetProgramInfoLogFunction) (GLuint program, GLsizei maxLength, GLsizei *length, char *infoLog);
	/**
	 * A function pointer for the glGetUniformLocation function.
	 */
	typedef GLint(__stdcall* pv_glGetUniformLocationFunction) (GLuint program, const char* name);
	/**
	 * A function pointer for the glUniform1f function.
	 */
	typedef void(__stdcall* pv_glUniform1fFunction) (GLint location, GLfloat v0);
	/**
	 * A function pointer for the glUniform2f function.
	 */
	typedef void(__stdcall* pv_glUniform2fFunction) (GLint location, GLfloat v0, GLfloat v1);
	/**
	 * A function pointer for the glUniform3f function.
	 */
	typedef void(__stdcall* pv_glUniform3fFunction) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
	/**
	 * A function pointer for the glUniform4f function.
	 */
	typedef void(__stdcall* pv_glUniform4fFunction) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
	/**
	 * A function pointer for the glUniformMatrix4fv function.
	 */
	typedef void(__stdcall* pv_glUniformMatrix4fvFunction) (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);

	/**
	* A function pointer for the glGenVertexArrays function.
	*/
	typedef void(__stdcall* pv_glGenVertexArraysFunction) (GLsizei n, GLuint* arrays);
	/**
	* A function pointer for the glBindVertexArray function.
	*/
	typedef void(__stdcall* pv_glBindVertexArrayFunction) (GLuint array);
	/**
	* A function pointer for the glGenBuffers function.
	*/
	typedef void(__stdcall* pv_glGenBuffersFunction) (GLsizei n, GLuint * buffers);
	/**
	* A function pointer for the glBindBuffer function.
	*/
	typedef void(__stdcall* pv_glBindBufferFunction) (GLenum target, GLuint buffer);
	/**
	* A function pointer for the glBufferData function.
	*/
#ifdef _WIN64
	typedef void(__stdcall* pv_glBufferDataFunction) (GLenum target, signed long long int size, const GLvoid * data, GLenum usage);
#else
	typedef void(__stdcall* pv_glBufferDataFunction) (GLenum target, signed long int size, const GLvoid * data, GLenum usage);
#endif
	/**
	* A function pointer for the glEnableVertexAttribArray function.
	*/
	typedef void(__stdcall* pv_glEnableVertexAttribArrayFunction) (GLuint index);
	/**
	* A function pointer for the glVertexAttribPointer function.
	*/
	typedef void(__stdcall* pv_glVertexAttribPointerFunction) (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer);

	typedef void(__stdcall* pv_glActiveTextureFunction) (GLenum texture);

	typedef void(__stdcall* pv_glBindAttribLocationFunction) (GLuint program, GLuint index, const char* name);

	typedef void(__stdcall* pv_glBindFragDataLocationFunction) (GLuint program, GLuint colorNumber, const char* name);

	/**
	 * The OpenGL method "glCreateShader", to be grabbed as an OpenGL extension.
	 *
	 * Definition from http://www.khronos.org/ (http://www.khronos.org/opengles/sdk/docs/man/xhtml/glCreateShader.xml):
	 *
	 * glCreateShader creates an empty shader object and returns a non-zero value by which it can be referenced. A shader
	 * object is used to maintain the source code strings that define a shader. shaderType indicates the type of shader
	 * to be created. Two types of shaders are supported. A shader of type GL_VERTEX_SHADER is a shader that is intended
	 * to run on the programmable vertex processor. A shader of type GL_FRAGMENT_SHADER is a shader that is intended to
	 * run on the programmable fragment processor.
	 *
	 * When created, a shader object's GL_SHADER_TYPE parameter is set to either GL_VERTEX_SHADER or GL_FRAGMENT_SHADER,
	 * depending on the value of shaderType.
	 *
	 * @param shaderType Specifies the type of shader to be created. Must be either GL_VERTEX_SHADER or GL_FRAGMENT_SHADER.
	 * @return This function returns 0 if an error occurs creating the shader object.  GL_INVALID_ENUM is generated if shaderType
	 * is not an accepted value.
	 */
	extern pv_glCreateShaderFunction pv_glCreateShader;

	/**
	 * The OpenGL method "glShaderSource", to be grabbed as an OpenGL extension.
	 *
	 * Definition from http://www.khronos.org/ (http://www.khronos.org/opengles/sdk/docs/man/xhtml/glShaderSource.xml):
	 *
	 * For implementations that support a shader compiler, glShaderSource sets the source code in shader to the source code
	 * in the array of strings specified by string. Any source code previously stored in the shader object is completely
	 * replaced. The number of strings in the array is specified by count. If length is NULL, each string is assumed to be
	 * null terminated. If length is a value other than NULL, it points to an array containing a string length for each of
	 * the corresponding elements of string. Each element in the length array may contain the length of the corresponding
	 * string (the null character is not counted as part of the string length) or a value less than 0 to indicate that the
	 * string is null terminated. The source code strings are not scanned or parsed at this time; they are simply copied into
	 * the specified shader object.
	 *
	 * @param shader Specifies the handle of the shader object whose source code is to be replaced.
	 * @param count Specifies the number of elements in the string and length arrays.
	 * @param string Specifies an array of pointers to strings containing the source code to be loaded into the shader.
	 * @param length Specifies an array of string lengths.
	 */
	extern pv_glShaderSourceFunction pv_glShaderSource;

	/**
	 * The OpenGL method "glCompileShader", to be grabbed as an OpenGL extension.
	 *
	 * Definition from http://www.khronos.org/ (http://www.khronos.org/opengles/sdk/docs/man/xhtml/glCompileShader.xml):
	 *
	 * For implementations that support a shader compiler, glCompileShader compiles the source
	 * code strings that have been stored in the shader object specified by shader.
	 *
	 * The compilation status will be stored as part of the shader object's state. This value will be set to GL_TRUE
	 * if the shader was compiled without errors and is ready for use, and GL_FALSE otherwise. It can be queried by
	 * calling glGetShaderiv with arguments shader and GL_COMPILE_STATUS.
	 *
	 * Compilation of a shader can fail for a number of reasons as specified by the OpenGL ES Shading Language Specification.
	 * Whether or not the compilation was successful, information about the compilation can be obtained from the shader object's
	 * information log by calling glGetShaderInfoLog.
	 *
	 * @param shader Specifies the shader object to be compiled.
	 */
	extern pv_glCompileShaderFunction pv_glCompileShader;

	/**
	 * The OpenGL method "glDeleteShader", to be grabbed as an OpenGL extension.
	 *
	 * Definition from http://www.khronos.org/ (http://www.khronos.org/opengles/sdk/docs/man/xhtml/glDeleteShader.xml):
	 *
	 * glDeleteShader frees the memory and invalidates the name associated with the shader object specified by shader. This
	 * command effectively undoes the effects of a call to glCreateShader.
	 *
	 * If a shader object to be deleted is attached to a program object, it will be flagged for deletion, but it will not be
	 * deleted until it is no longer attached to any program object, for any rendering context (i.e., it must be detached from
	 * wherever it was attached before it will be deleted). A value of 0 for shader will be silently ignored.
	 *
	 * To determine whether an object has been flagged for deletion, call glGetShaderiv with arguments shader and GL_DELETE_STATUS.
	 *
	 * @param shader Specifies the shader object to be compiled.
	 */
	extern pv_glDeleteShaderFunction pv_glDeleteShader;

	/**
	* The OpenGL method "glGetShaderiv", to be grabbed as an OpenGL extension.
	*
	* Definition from http://www.khronos.org/ (http://www.khronos.org/opengles/sdk/docs/man/xhtml/glGetShaderiv.xml):
	*
	* glGetShaderiv returns in params the value of a parameter for a specific shader object. The following parameters are defined:
	*
	* 	GL_SHADER_TYPE
	* params returns GL_VERTEX_SHADER if shader is a vertex shader object, and GL_FRAGMENT_SHADER if shader is a fragment shader object.
	*
	* GL_DELETE_STATUS
	* params returns GL_TRUE if shader is currently flagged for deletion, and GL_FALSE otherwise.
	*
	* GL_COMPILE_STATUS
	* For implementations that support a shader compiler, params returns GL_TRUE if the last compile operation on shader was successful, 
	* and GL_FALSE otherwise.
	*
	* GL_INFO_LOG_LENGTH
	* For implementations that support a shader compiler, params returns the number of characters in the information log for shader 
	* including the null termination character (i.e., the size of the character buffer required to store the information log). If 
	* shader has no information log, a value of 0 is returned.
	*
	* GL_SHADER_SOURCE_LENGTH
	* For implementations that support a shader compiler, params returns the length of the concatenation of the source strings that 
	* make up the shader source for the shader, including the null termination character. (i.e., the size of the character buffer 
	* required to store the shader source). If no source code exists, 0 is returned.
	*
	* @param shader Specifies the shader object to be queried.
	* @param pname Specifies the object parameter. Accepted symbolic names are GL_SHADER_TYPE, GL_DELETE_STATUS, GL_COMPILE_STATUS, 
	* GL_INFO_LOG_LENGTH, GL_SHADER_SOURCE_LENGTH.
	* @param params Returns the requested object parameter.
	*/
	extern pv_glGetShaderivFunction pv_glGetShaderiv;

	/**
	* The OpenGL method "glGetShaderInfoLog", to be grabbed as an OpenGL extension.
	*
	* Definition from http://www.khronos.org/ (http://www.khronos.org/opengles/sdk/docs/man/xhtml/glGetShaderInfoLog.xml):
	*
	* glGetShaderInfoLog returns the information log for the specified shader object. The information log for a shader object is
	* modified when the shader is compiled. The string that is returned will be null terminated.
	*
	* glGetShaderInfoLog returns in infoLog as much of the information log as it can, up to a maximum of maxLength characters. 
	* The number of characters actually returned, excluding the null termination character, is specified by length. If the length 
	* of the returned string is not required, a value of NULL can be passed in the length argument. The size of the buffer required 
	* to store the returned information log can be obtained by calling glGetShaderiv with the value GL_INFO_LOG_LENGTH.
	*
	* The information log for a shader object is a string that may contain diagnostic messages, warning messages, 
	* and other information about the last compile operation. When a shader object is created, its information log will be a string 
	* of length 0.
	*
	* @param shader Specifies the shader object whose information log is to be queried.
	* @param maxLength Specifies the size of the character buffer for storing the returned information log.
	* @param length Returns the length of the string returned in infoLog (excluding the null terminator).
	* @param infoLog Specifies an array of characters that is used to return the information log.
	*/
	extern pv_glGetShaderInfoLogFunction pv_glGetShaderInfoLog;

	/**
	 * The OpenGL method "glCreateProgram", to be grabbed as an OpenGL extension.
	 *
	 * Definition from http://www.khronos.org/ (http://www.khronos.org/opengles/sdk/docs/man/xhtml/glCreateProgram.xml):
	 *
	 * glCreateProgram creates an empty program object and returns a non-zero value by which it can be referenced.
	 * A program object is an object to which shader objects can be attached. This provides a mechanism to specify the
	 * shader objects that will be linked to create a program. It also provides a means for checking the compatibility
	 * of the shaders that will be used to create a program (for instance, checking the compatibility between a vertex
	 * shader and a fragment shader). When no longer needed as part of a program object, shader objects can be detached.
	 *
	 * One or more executables are created in a program object by successfully attaching shader objects to it with
	 * glAttachShader, successfully compiling the shader objects with glCompileShader, and successfully linking the program
	 * object with glLinkProgram. These executables are made part of current state when glUseProgram is called. Program objects
	 * can be deleted by calling glDeleteProgram. The memory associated with the program object will be deleted when it is no
	 * longer part of current rendering state for any context.
	 *
	 * @return This function returns 0 if an error occurs creating the program object.
	 */
	extern pv_glCreateProgramFunction pv_glCreateProgram;

	/**
	 * The OpenGL method "glAttachShader", to be grabbed as an OpenGL extension.
	 *
	 * Definition from http://www.khronos.org/ (http://www.khronos.org/opengles/sdk/docs/man/xhtml/glAttachShader.xml):
	 *
	 * In order to create an executable, there must be a way to specify the list of things that will be
	 * linked together. Program objects provide this mechanism. Shaders that are to be linked together in a
	 * program object must first be attached to that program object. glAttachShader attaches the shader object
	 * specified by shader to the program object specified by program. This indicates that shader will be included
	 * in link operations that will be performed on program.
	 *
	 * All operations that can be performed on a shader object are valid whether or not the shader object is attached to a program
	 * object. It is permissible to attach a shader object to a program object before source code has been loaded into the shader
	 * object or before the shader object has been compiled. Multiple shader objects of the same type may not be attached to a
	 * single program object. However, a single shader object may be attached to more than one program object. If a shader object
	 * is deleted while it is attached to a program object, it will be flagged for deletion, and deletion will not occur until
	 * glDetachShader is called to detach it from all program objects to which it is attached.
	 *
	 * @param program Specifies the program object to which a shader object will be attached.
	 * @param shader Specifies the shader object that is to be attached.
	 */
	extern pv_glAttachShaderFunction pv_glAttachShader;

	/**
	* The OpenGL method "glAttachShader", to be grabbed as an OpenGL extension.
	*
	* Definition from http://www.khronos.org/ (http://www.khronos.org/opengles/sdk/docs/man/xhtml/glLinkProgram.xml):
	*
	* glLinkProgram links the program object specified by program. Shader objects of type GL_VERTEX_SHADER attached to program
	* are used to create an executable that will run on the programmable vertex processor. Shader objects of type GL_FRAGMENT_SHADER
	* attached to program are used to create an executable that will run on the programmable fragment processor.
	*
	* The status of the link operation will be stored as part of the program object's state. This value will be set to GL_TRUE if
	* the program object was linked without errors and is ready for use, and GL_FALSE otherwise. It can be queried by calling glGetProgramiv
	* with arguments program and GL_LINK_STATUS.
	*
	* As a result of a successful link operation, all active user-defined uniform variables belonging to program will be initialized to 0,
	* and each of the program object's active uniform variables will be assigned a location that can be queried by calling
	* glGetUniformLocation. Also, any active user-defined attribute variables that have not been bound to a generic vertex attribute
	* index will be bound to one at this time.
	*
	* Linking of a program object can fail for a number of reasons as specified in the OpenGL ES Shading Language Specification. The
	* following lists some of the conditions that will cause a link error.
	*
	* *A vertex shader and a fragment shader are not both present in the program object.
	*
	* *The number of active attribute variables supported by the implementation has been exceeded.
	*
	* The storage limit for uniform variables has been exceeded.
	*
	* *The number of active uniform variables supported by the implementation has been exceeded.
	*
	* *The main function is missing for the vertex shader or the fragment shader.
	*
	* *A varying variable actually used in the fragment shader is not declared in the same way (or is not declared at all) in the vertex
	* shader.
	*
	* *A reference to a function or variable name is unresolved.
	*
	* *A shared global is declared with two different types or two different initial values.
	*
	* *One or more of the attached shader objects has not been successfully compiled (via glCompileShader) or loaded with a pre-compiled
	* shader binary (via glShaderBinary).
	*
	* *Binding a generic attribute matrix caused some rows of the matrix to fall outside the allowed maximum of GL_MAX_VERTEX_ATTRIBS.
	*
	* *Not enough contiguous vertex attribute slots could be found to bind attribute matrices.
	*
	* When a program object has been successfully linked, the program object can be made part of current state by calling
	* glUseProgram. Whether or not the link operation was successful, the program object's information log will be overwritten. The
	* information log can be retrieved by calling glGetProgramInfoLog.
	*
	* glLinkProgram will also install the generated executables as part of the current rendering state if the link operation was
	* successful and the specified program object is already currently in use as a result of a previous call to glUseProgram. If
	* the program object currently in use is relinked unsuccessfully, its link status will be set to GL_FALSE , but the executables
	* and associated state will remain part of the current state until a subsequent call to glUseProgram removes it from use. After
	* it is removed from use, it cannot be made part of current state until it has been successfully relinked.
	*
	* The program object's information log is updated and the program is generated at the time of the link operation. After the link
	* operation, applications are free to modify attached shader objects, compile attached shader objects, detach shader objects,
	* delete shader objects, and attach additional shader objects. None of these operations affects the information log or the program
	* that is part of the program object.
	*
	* @param program Specifies the handle of the program object to be linked.
	*/
	extern pv_glLinkProgramFunction pv_glLinkProgram;

	/**
	* The OpenGL method "glGetUniformLocation", to be grabbed as an OpenGL extension.
	*
	* Definition from http://www.khronos.org/ (http://www.khronos.org/opengles/sdk/docs/man/xhtml/glGetUniformLocation.xml):
	*
	* glUseProgram installs the program object specified by program as part of current rendering state. One or more executables 
	* are created in a program object by successfully attaching shader objects to it with glAttachShader, successfully compiling
	* the shader objects with glCompileShader, and successfully linking the program object with glLinkProgram.
	*
	* A program object will contain executables that will run on the vertex and fragment processors if it contains one or more shader 
	* objects of type GL_VERTEX_SHADER and one or more shader objects of type GL_FRAGMENT_SHADER that have all been successfully 
	* compiled and linked.
	*
	* While a program object is in use, applications are free to modify attached shader objects, compile attached shader objects, attach 
	* additional shader objects, and detach or delete shader objects. None of these operations will affect the executables that are 
	* part of the current state. However, relinking the program object that is currently in use will install the program object as 
	* part of the current rendering state if the link operation was successful (see glLinkProgram ). If the program object currently 
	* in use is relinked unsuccessfully, its link status will be set to GL_FALSE, but the executables and associated state will remain 
	* part of the current state until a subsequent call to glUseProgram removes it from use. After it is removed from use, it cannot 
	* be made part of current state until it has been successfully relinked.
	*
	* If program is 0, then the current rendering state refers to an invalid program object, and the results of vertex and fragment 
	* shader execution due to any glDrawArrays or glDrawElements commands are undefined.
	*
	* @param program Specifies the handle of the program object whose executables are to be used as part of current rendering state.
	*/
	extern pv_glUseProgramFunction pv_glUseProgram;

	/**
	* The OpenGL method "glGetUniformLocation", to be grabbed as an OpenGL extension.
	*
	* Definition from http://www.khronos.org/ (http://www.khronos.org/opengles/sdk/docs/man/xhtml/glGetUniformLocation.xml):
	*
	* glGetUniformLocation returns an integer that represents the location of a specific uniform variable within a program object. 
	* name must be a null terminated string that contains no white space. name must be an active uniform variable name in program 
	* that is not a structure, an array of structures, or a subcomponent of a vector or a matrix. This function returns -1 if name 
	* does not correspond to an active uniform variable in program or if name starts with the reserved prefix "gl_".
	*
	* Uniform variables that are structures or arrays of structures may be queried by calling glGetUniformLocation for each field 
	* within the structure. The array element operator "[]" and the structure field operator "." may be used in name in order to 
	* select elements within an array or fields within a structure. The result of using these operators is not allowed to be another 
	* structure, an array of structures, or a subcomponent of a vector or a matrix. Except if the last part of name indicates a 
	* uniform variable array, the location of the first element of an array can be retrieved by using the name of the array, or by 
	* using the name appended by "[0]".
	*
	* The actual locations assigned to uniform variables are not known until the program object is linked successfully. After linking 
	* has occurred, the command glGetUniformLocation can be used to obtain the location of a uniform variable. This location value can 
	* then be passed to glUniform to set the value of the uniform variable or to glGetUniform in order to query the current value of 
	* the uniform variable. After a program object has been linked successfully, the index values for uniform variables remain fixed 
	* until the next link command occurs. Uniform variable locations and values can only be queried after a link if the link was 
	* successful.
	*
	* @param program Specifies the program object to be queried.
	* @param name Points to a null terminated string containing the name of the uniform variable whose location is to be queried.
	* @return GL_INVALID_VALUE is generated if program is not a value generated by OpenGL.
	* GL_INVALID_OPERATION is generated if program is not a program object.
	* GL_INVALID_OPERATION is generated if program has not been successfully linked.
	*/
	extern pv_glGetUniformLocationFunction pv_glGetUniformLocation;

	extern pv_glGetProgramivFunction pv_glGetProgramiv;
	extern pv_glGetProgramInfoLogFunction pv_glGetProgramInfoLog;

	extern pv_glUniform1fFunction pv_glUniform1f;

	extern pv_glUniform2fFunction pv_glUniform2f;

	extern pv_glUniform3fFunction pv_glUniform3f;

	extern pv_glUniform4fFunction pv_glUniform4f;

	extern pv_glUniformMatrix4fvFunction pv_glUniformMatrix4fv;

	extern pv_glGenVertexArraysFunction pv_glGenVertexArrays;
	extern pv_glBindVertexArrayFunction pv_glBindVertexArray;
	extern pv_glGenBuffersFunction pv_glGenBuffers;
	extern pv_glBindBufferFunction pv_glBindBuffer;
	extern pv_glBufferDataFunction pv_glBufferData;
	extern pv_glEnableVertexAttribArrayFunction pv_glEnableVertexAttribArray;
	extern pv_glVertexAttribPointerFunction pv_glVertexAttribPointer;
	extern pv_glActiveTextureFunction pv_glActiveTexture;

	extern pv_glBindAttribLocationFunction pv_glBindAttribLocation;
	extern pv_glBindFragDataLocationFunction pv_glBindFragDataLocation;

	/**
	 * Initializes the minimum required OpenGL functions for use with Project Virtua.  All of these methods are prefixed with pv_ in order
	 * to prevent compiler issues with OpenGL extension libraries.  These methods are included so that only the necessary OpenGL methods
	 * are added for smaller file sizes and such.
	 */
	void initMinGL();
};
#endif