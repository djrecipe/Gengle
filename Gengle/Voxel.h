#pragma once
#include <GLEW/1.11.0/glew.h> 
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

typedef unsigned char GLuchar;
using namespace std;
/// <summary>A class which represents a single perfectly cubic area of space. This area of space is represented by an origin, which is the very center of the cube, and
/// the "density" values at the volume's 8 corners. Density values which are greater than 0 are considered outside space, while density values less than or equal to 0 are considered
/// "in the ground". Voxel values are processed using a technique known as "Marching Cubes" which utilizes some look-up tables  - which I will not explain here - that result in fairly flexible
/// mesh arrangements whose limitations can be aleved via further processing / algorithmic enhancements.
/// <seealso cref="VoxelField"/><seealso cref="SurfaceNet"/><seealso cref="BlockArray"/></summary>
/// <remarks>A collection of instances of this class is managed via a VoxelField.</remarks>
class Voxel
{
protected:
    //--- Static Class Variables ---//
    /// <summary>Three collections of four unsigned short integers which represent the indices of all of the edges which are aligned on each of the three axis in 3D space. The first collection of
    /// four unsigned shorts represents the four edges which align with the x-axis, the second collection represents the edges which align with the y-axis, and the last collection represents
    /// the indices of the edges which align with the z-axis. This information is the same for every voxel and is used to determine which axis each generated vertex will be interpolated on.
    /// <seealso cref="Voxel::EdgesOfIndex"/><seealso cref="Voxel::SetMarchingCubesParameters()"/></summary>
    /// <remarks>The order of the four elements in each four element container is arbitrary and thus the edges are ordered in a logical order, as opposed to ordering them by rotation, etc.</remarks>
    static GLushort EdgesByAxis[3][4];
    /// <summary>Twelve collections of two unsigned short integers which represent the indices of the two corners which form the end points of each of the twelve possible edges of the voxel. Once it
    /// has been determined which edges the vertices lie on for the given voxel configuration, the indices of the edge that each vertex lies on is used to index into this collection of twelve pairs of
    /// [different] indices. These new pair of indices are used in order to index into <c>Voxel::corners</c> and subsequently generate a vertex by interpolating the vertices that lie at two corners
    /// according to the density values at those corners. <seealso cref="Voxel::EdgesByAxis"/><seealso cref="Voxel::corners"/><seealso cref="Voxel::SetMarchingCubesParameters()"/></summary>
    /// <remarks>Each index into the outer collection of this member corresponds to the edge index.</remarks>
    static GLushort CornersOfEdge[12][2];
    /// <summary>A collection of 256 8-bit numbers which indicate the number of vertices which result from each of the 256 possible voxel configurations - for quick creation of arrays.
    /// <seealso cref="Voxel::num_vertices"/><seealso cref="Voxel::EdgesOfIndex"/></summary>
    /// <remarks>There will never be more than 15 vertices (or 45 total numbers since there 3 components to each vertex) in a single voxel.</remarks>
    static GLchar VerticeCount[256];
    /// <summary>256 collections of fifteen indices which serve as the bread-and-butter to the Marching Cube algorithm - each of the collection of fifteen indices represents the fifteen edges on
    /// which the vertices of a given voxel arrangement lie, while the index into the outermost 256-element array represents each of the 256 (2^8 where 8 is the number of corners in a voxel) possible
    /// voxel configurations. The index into this outermost 256-element array can be determined by determining the sign of the density values in each corner of the voxel and performing a bitwise AND
    /// to combine the "inside/outside" status of all 8 corners into a single 8-bit number which can be used as the index.</summary>
    /// <remarks>Figuring out these indices was difficult and is dependent upon the specific Marching Cubes algorithm that is used. Our algorithm (courtesy of Eric Lengyel's dissertation) supposadely
    /// contains zero amiguous configurations which should theoretically render it "unbreakable". Indices are stored as chars since there will be no edge index above 15.</remarks>
    static GLchar EdgesOfIndex[256][15];
    /// <summary>An array of indices (into <c>Voxel::VerticeCount</c> and <c>Voxel::EdgesOfIndex</c>) which indicate which of the 256 possible voxel configurations must be inverted (from its "equivalent 
    /// case" - something I won't cover here). This member is currently not being utilized but may be utilized for debugging purposes if needed.</summary>
    static GLuchar InvertedIndices[];
    static GLushort Voxel::EdgesByRegion[3][2][4];
    //--- Protected Variables ---//
    /// <summary>A three element array of floats which represent the x,y, and z components of the very middle of the cubic area represented by the voxel. This center value is used in order to determine
    /// the vertices at the corner of the voxel and subsequently the generated interpolated vertices which lie on its edge. This value could also be used for operations such as proximity checks.
    /// <seealso cref="Voxel::corners"/><seealso cref="Voxel::Voxel()"/></summary>
    /// <remarks>This member is initialized directly via the parameters passed to the constructor of this class.</remarks>
    GLfloat origin[3];
    /// <summary>A collection of three element float arrays which represent the x,y, and z components of the vertices of the eights corners of the cubic area represented by the voxel. These vertices
    /// are used to generate vertices by interpolating two adjacent corners according to the voxel configuration.
    /// <seealso cref="Voxel::origin"/><seealso cref="Voxel::Voxel()"/></summary>
    /// <remarks>Initialized in the constructor by adding or subtracting <c>Voxel::radius</c> from <c>Voxel::origin</c> along various axis.</remarks>
    GLfloat corners[8][3];
    /// <summary>A float representing the distance from the center of the cubic area represented by the voxel and the middle of any of the voxel's faces. In other words, it is half of the width of the 
    /// cubic area represented by the voxel. <seealso cref="Voxel::Voxel()"/></summary>
    /// <remarks>Initialized directly via a parameter passed to the constructor of this class.</remarks>
    GLfloat radius;
    /// <summary>A signed short integer which represents the index of this voxel's configuration into Marching Cubes' 256 possible configurations (2^8). This number is the primary number that determines
    /// "what the voxel will look like" - or more specifically the edges on which vertices will lie and the direction normals will face. This number is calculated by iterating through the corners of the
    /// voxel and adding 2 to the power of the sign of the corner value (1 if the corner value is negative; 0 if the corner value is positive).</summary>
    /// <remarks>Initialized to _BAD (-1) in this class's constructor and set to a proper index in <c>Voxel::SetMarchingCubesParameters()</c>. If this value is 0 or 255 then no vertices will be rendered.</remarks>
    GLshort marchingCubeCase;
    /// <summary>An 8-bit number representing the number of vertex components this voxel currently contains. This number represents the number of floating point numbers (the x,y, and z components for each
    /// of the up-to 15 vertices) - not the number of vertices (which will be this value divided by three) - and will/should never exceed 45 (thus this number only need be 8-bit).
    /// <seealso cref="Voxel::SetMarchingCubesParameters()"/></summary>
    /// <remarks>Initialized to 0 in this class's constructor and modified again in <c>Voxel::SetMarchingCubesParameters()</c>.</remarks>
    GLchar num_vertices;
public:
    //--- Public Methods ---//
    // ~ Constructor(s)
    /// <summary>The sole constructor for this class which requires four floats as parameters, the first three of which represent the x,y, and z components of the very center of the voxel. This coordinate
    /// will determine where the corners of the voxel will be located and ultimately where the vertices will be generated. The fourth parameter required is the "radius" of the cube, or the half the width
    /// of any given edge - this parameter will determine how "large" the voxel is.
    /// <seealso cref="Voxel::SetMarchingCubesParameters()"/></summary>
    /// <param name="x_in">A float representing the x component of the coordinate at which the voxel will be located/centered on.</param>
    /// <param name="y_in">A float representing the y component of the coordinate at which the voxel will be located/centered on.</param>
    /// <param name="z_in">A float representing the z component of the coordinate at which the voxel will be located/centered on.</param>
    /// <param name="radius_in">A float representing the distance between the center of the voxel and the center of any of its faces. In other words, this is half the length of any of the edges
    /// of the cubic area represented by the voxel. Ultimately this value determines how large the voxel is.</param>
    /// <remarks>This constructor does not determine the voxel configuration or the actual vertices that will be rendered - that is determined in <c>Voxel::SetMarchingCubesParameters()</c>.</remarks>
    Voxel(GLfloat x_in, GLfloat y_in, GLfloat z_in, GLfloat radius_in);
    // ~ Operator(s)
    /// <summary>Assignment operator method. This method is called whenever a Voxel is on the left-hand side of an '=' operator and is responsible for responsibley freeing any memory exclusively owned
    /// by the Voxel class and then copying the data from the Voxel instance found on the right-hand side of the '=' operator into its own members.</summary>
    /// <param name="voxel_in">The Voxel instance which will be copied to the target (invoking) instance.</param>
    /// <returns>Trivially returns a reference to the type. Return type could be void as well.</returns>
    /// <remarks>Be sure to check for anomolies (such as self-assignment) when coding this method. An example invocation of this method is <c>foo=bar;</c> where foo and bar are both predefined Voxel
    /// instances.</remarks>
    Voxel& operator=(const Voxel & voxel_in);
    // ~ Configuration
    /// <summary>This method directly sets the density values at all eight corners of the voxel, determines the resulting Marching Cubes case index for this voxel, then adds the appropriate NetNodes
    /// and NetNode neighbors to a SurfaceNet passed as a parameter. The Marching Cubes case number is determined by iterating through the corner values and adding 2^(index into corner_vals array)
    /// for each corner value that is less than zero. Various look up tables are accessed / iterated through until the algorithm has determined the pairs of coordinates (voxel corners) which need to
    /// be interpolated and their interpolation ratio. The voxels corners are interpolated according to their density values so that a surface is created where f(x)=0. The maximum amount of vertices
    /// that will be generated for any given voxel is 15 (45 floats total). <seealso cref="VoxelField::FillWithRandom()"/><seealso cref="Voxel::EdgesOfIndex"/><seealso cref="Voxel::EdgesByAxis"/>
    /// <seealso cref="Voxel::CornersOfEdge"/></summary>
    /// <param name="corner_vals">An array of eight characters (actually 8-bit numbers) which represent the density values at each of the eight corners of the voxel. A positive density value means
    /// the corner lies outside "solid matter" whereas a zero or a negative number implies the corner lies inside "solid matter". Combined, the density values at all eight corners of the voxel
    /// determine the "voxel configuration" and "Marching Cubes casde index" for the voxel. It is expected that each corner value is within the range of -255 to +255, and if a nice-looking continuous
    /// mesh is desired, then a combination of noise functions should be used in order to generate the corner values.</param>
    /// <param name="target_edges">An array of eight unsigned integers which will be populated by this method with the fifteen indices of the edges on which the voxel's generated vertices will lie.
    /// If less than fifteen vertices are generated then the remaining elements are populated with the value '-1'. These edges are ultimately converted into a global edge index (an index that is 
    /// unique to all edges across all voxels) then the global edge index is used to blend normals which share an edge - a process which could easily be accomplished via the SurfaceNet class which
    /// already has the structure for such an operation. In other words, I expect this parameter to be removed/deprecated at some point in the near future.</param>
    /// <param name="net_in">A reference to an existing SurfaceNet to which the generated vertices (NetNodes) will be added. This method takes care of populating each NetNode with its appropriate
    /// neighbors, as well.</param>
    /// <returns>An unsigned integer representing the number of vertices generated by this method. This number will always range from 0 to 15.</returns>
    /// <remarks>Normal blending should be moved to the SurfaceNet class soon.</remarks>
    //GLuint SetMarchingCubesParameters(GLchar corner_vals[8],SurfaceNet & net_in, bool limit[3][2]);
    vector<glm::vec3> SetMarchingCubesParameters(GLchar corner_vals[8], bool limit[3][2]);
    ///// <summary>A method which takes a LineStrip as a parameter and adds the 12 line segments which represent the edges of the voxel. This technique can be used in order to display the gridlines
    ///// on which all vertices will fall (not counting post processing such as relaxation techniques).<seealso cref="LineStrip::AddInstance()"/><seealso cref="Voxel::SetMarchingCubesParameters()"/></summary>
    ///// <param name="line_in">A reference to an existing LineStrip to which the voxel edge line segments will be added.</param>
    ///// <returns>An integer indicating the success of the method. Currently always returns _OK (0).</returns>
    ///// <remarks>Used primarily for debugging purposes. Note that this method will result in a very high number of line segments should the voxel gridlines be displayed for all voxels.</remarks>
    //GLint AddCubeMesh(LineStrip & line_in);
    // ~ Destructor
    /// <summary>The destructor for the Voxel class which is responsible for freeing any memory which was dynamically allocated in a Voxel method.</summary>
    /// <remarks>Declared virtual as a stylistic choice.</remarks>
    virtual ~Voxel(void);//
};

