#include <assert.h>
#include <string.h>

#include "state_writer.hpp"
#include "scoped_allocator.hpp"
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#include "glsize.hpp"
#include "glstate.hpp"
#include "glstate_internal.hpp"

namespace glstate {

const char *
enumToString(GLenum pname)
{
    switch (pname) {
    case GL_ZERO:
        return "GL_ZERO";
    case GL_ONE:
        return "GL_ONE";
    case GL_RESTART_PATH_NV:
        return "GL_RESTART_PATH_NV";
    case GL_DUP_FIRST_CUBIC_CURVE_TO_NV:
        return "GL_DUP_FIRST_CUBIC_CURVE_TO_NV";
    case GL_DUP_LAST_CUBIC_CURVE_TO_NV:
        return "GL_DUP_LAST_CUBIC_CURVE_TO_NV";
    case GL_RECT_NV:
        return "GL_RECT_NV";
    case GL_RELATIVE_RECT_NV:
        return "GL_RELATIVE_RECT_NV";
    case GL_CIRCULAR_CCW_ARC_TO_NV:
        return "GL_CIRCULAR_CCW_ARC_TO_NV";
    case GL_CIRCULAR_CW_ARC_TO_NV:
        return "GL_CIRCULAR_CW_ARC_TO_NV";
    case GL_CIRCULAR_TANGENT_ARC_TO_NV:
        return "GL_CIRCULAR_TANGENT_ARC_TO_NV";
    case GL_ARC_TO_NV:
        return "GL_ARC_TO_NV";
    case GL_RELATIVE_ARC_TO_NV:
        return "GL_RELATIVE_ARC_TO_NV";
#ifndef GL_ES_VERSION_3_0
    case GL_ACCUM:
        return "GL_ACCUM";
    case GL_LOAD:
        return "GL_LOAD";
    case GL_RETURN:
        return "GL_RETURN";
    case GL_MULT:
        return "GL_MULT";
    case GL_ADD:
        return "GL_ADD";
#endif
    case GL_NEVER:
        return "GL_NEVER";
    case GL_LESS:
        return "GL_LESS";
    case GL_EQUAL:
        return "GL_EQUAL";
    case GL_LEQUAL:
        return "GL_LEQUAL";
    case GL_GREATER:
        return "GL_GREATER";
    case GL_NOTEQUAL:
        return "GL_NOTEQUAL";
    case GL_GEQUAL:
        return "GL_GEQUAL";
    case GL_ALWAYS:
        return "GL_ALWAYS";
    case GL_SRC_COLOR:
        return "GL_SRC_COLOR";
    case GL_ONE_MINUS_SRC_COLOR:
        return "GL_ONE_MINUS_SRC_COLOR";
    case GL_SRC_ALPHA:
        return "GL_SRC_ALPHA";
    case GL_ONE_MINUS_SRC_ALPHA:
        return "GL_ONE_MINUS_SRC_ALPHA";
    case GL_DST_ALPHA:
        return "GL_DST_ALPHA";
    case GL_ONE_MINUS_DST_ALPHA:
        return "GL_ONE_MINUS_DST_ALPHA";
    case GL_DST_COLOR:
        return "GL_DST_COLOR";
    case GL_ONE_MINUS_DST_COLOR:
        return "GL_ONE_MINUS_DST_COLOR";
    case GL_SRC_ALPHA_SATURATE:
        return "GL_SRC_ALPHA_SATURATE";
#ifndef GL_ES_VERSION_3_0
    case GL_FRONT_LEFT:
        return "GL_FRONT_LEFT";
    case GL_FRONT_RIGHT:
        return "GL_FRONT_RIGHT";
    case GL_BACK_LEFT:
        return "GL_BACK_LEFT";
    case GL_BACK_RIGHT:
        return "GL_BACK_RIGHT";
#endif
    case GL_FRONT:
        return "GL_FRONT";
    case GL_BACK:
        return "GL_BACK";
#ifndef GL_ES_VERSION_3_0
    case GL_LEFT:
        return "GL_LEFT";
    case GL_RIGHT:
        return "GL_RIGHT";
#endif
    case GL_FRONT_AND_BACK:
        return "GL_FRONT_AND_BACK";
#ifndef GL_ES_VERSION_3_0
    case GL_AUX0:
        return "GL_AUX0";
    case GL_AUX1:
        return "GL_AUX1";
    case GL_AUX2:
        return "GL_AUX2";
    case GL_AUX3:
        return "GL_AUX3";
#endif
    case GL_INVALID_ENUM:
        return "GL_INVALID_ENUM";
    case GL_INVALID_VALUE:
        return "GL_INVALID_VALUE";
    case GL_INVALID_OPERATION:
        return "GL_INVALID_OPERATION";
#ifndef GL_ES_VERSION_3_0
    case GL_STACK_OVERFLOW:
        return "GL_STACK_OVERFLOW";
    case GL_STACK_UNDERFLOW:
        return "GL_STACK_UNDERFLOW";
#endif
    case GL_OUT_OF_MEMORY:
        return "GL_OUT_OF_MEMORY";
    case GL_INVALID_FRAMEBUFFER_OPERATION:
        return "GL_INVALID_FRAMEBUFFER_OPERATION";
#ifndef GL_ES_VERSION_3_0
    case GL_CONTEXT_LOST:
        return "GL_CONTEXT_LOST";
    case GL_2D:
        return "GL_2D";
    case GL_3D:
        return "GL_3D";
    case GL_3D_COLOR:
        return "GL_3D_COLOR";
    case GL_3D_COLOR_TEXTURE:
        return "GL_3D_COLOR_TEXTURE";
    case GL_4D_COLOR_TEXTURE:
        return "GL_4D_COLOR_TEXTURE";
    case GL_PASS_THROUGH_TOKEN:
        return "GL_PASS_THROUGH_TOKEN";
    case GL_POINT_TOKEN:
        return "GL_POINT_TOKEN";
    case GL_LINE_TOKEN:
        return "GL_LINE_TOKEN";
    case GL_POLYGON_TOKEN:
        return "GL_POLYGON_TOKEN";
    case GL_BITMAP_TOKEN:
        return "GL_BITMAP_TOKEN";
    case GL_DRAW_PIXEL_TOKEN:
        return "GL_DRAW_PIXEL_TOKEN";
    case GL_COPY_PIXEL_TOKEN:
        return "GL_COPY_PIXEL_TOKEN";
    case GL_LINE_RESET_TOKEN:
        return "GL_LINE_RESET_TOKEN";
    case GL_EXP:
        return "GL_EXP";
    case GL_EXP2:
        return "GL_EXP2";
#endif
    case GL_CW:
        return "GL_CW";
    case GL_CCW:
        return "GL_CCW";
#ifndef GL_ES_VERSION_3_0
    case GL_COEFF:
        return "GL_COEFF";
    case GL_ORDER:
        return "GL_ORDER";
    case GL_DOMAIN:
        return "GL_DOMAIN";
    case GL_CURRENT_COLOR:
        return "GL_CURRENT_COLOR";
    case GL_CURRENT_INDEX:
        return "GL_CURRENT_INDEX";
    case GL_CURRENT_NORMAL:
        return "GL_CURRENT_NORMAL";
    case GL_CURRENT_TEXTURE_COORDS:
        return "GL_CURRENT_TEXTURE_COORDS";
    case GL_CURRENT_RASTER_COLOR:
        return "GL_CURRENT_RASTER_COLOR";
    case GL_CURRENT_RASTER_INDEX:
        return "GL_CURRENT_RASTER_INDEX";
    case GL_CURRENT_RASTER_TEXTURE_COORDS:
        return "GL_CURRENT_RASTER_TEXTURE_COORDS";
    case GL_CURRENT_RASTER_POSITION:
        return "GL_CURRENT_RASTER_POSITION";
    case GL_CURRENT_RASTER_POSITION_VALID:
        return "GL_CURRENT_RASTER_POSITION_VALID";
    case GL_CURRENT_RASTER_DISTANCE:
        return "GL_CURRENT_RASTER_DISTANCE";
    case GL_POINT_SMOOTH:
        return "GL_POINT_SMOOTH";
    case GL_POINT_SIZE:
        return "GL_POINT_SIZE";
    case GL_POINT_SIZE_RANGE:
        return "GL_POINT_SIZE_RANGE";
    case GL_POINT_SIZE_GRANULARITY:
        return "GL_POINT_SIZE_GRANULARITY";
    case GL_LINE_SMOOTH:
        return "GL_LINE_SMOOTH";
#endif
    case GL_LINE_WIDTH:
        return "GL_LINE_WIDTH";
#ifndef GL_ES_VERSION_3_0
    case GL_LINE_WIDTH_RANGE:
        return "GL_LINE_WIDTH_RANGE";
    case GL_LINE_WIDTH_GRANULARITY:
        return "GL_LINE_WIDTH_GRANULARITY";
    case GL_LINE_STIPPLE:
        return "GL_LINE_STIPPLE";
    case GL_LINE_STIPPLE_PATTERN:
        return "GL_LINE_STIPPLE_PATTERN";
    case GL_LINE_STIPPLE_REPEAT:
        return "GL_LINE_STIPPLE_REPEAT";
    case GL_LIST_MODE:
        return "GL_LIST_MODE";
    case GL_MAX_LIST_NESTING:
        return "GL_MAX_LIST_NESTING";
    case GL_LIST_BASE:
        return "GL_LIST_BASE";
    case GL_LIST_INDEX:
        return "GL_LIST_INDEX";
    case GL_POLYGON_MODE:
        return "GL_POLYGON_MODE";
    case GL_POLYGON_SMOOTH:
        return "GL_POLYGON_SMOOTH";
    case GL_POLYGON_STIPPLE:
        return "GL_POLYGON_STIPPLE";
    case GL_EDGE_FLAG:
        return "GL_EDGE_FLAG";
#endif
    case GL_CULL_FACE:
        return "GL_CULL_FACE";
    case GL_CULL_FACE_MODE:
        return "GL_CULL_FACE_MODE";
    case GL_FRONT_FACE:
        return "GL_FRONT_FACE";
#ifndef GL_ES_VERSION_3_0
    case GL_LIGHTING:
        return "GL_LIGHTING";
    case GL_LIGHT_MODEL_LOCAL_VIEWER:
        return "GL_LIGHT_MODEL_LOCAL_VIEWER";
    case GL_LIGHT_MODEL_TWO_SIDE:
        return "GL_LIGHT_MODEL_TWO_SIDE";
    case GL_LIGHT_MODEL_AMBIENT:
        return "GL_LIGHT_MODEL_AMBIENT";
    case GL_SHADE_MODEL:
        return "GL_SHADE_MODEL";
    case GL_COLOR_MATERIAL_FACE:
        return "GL_COLOR_MATERIAL_FACE";
    case GL_COLOR_MATERIAL_PARAMETER:
        return "GL_COLOR_MATERIAL_PARAMETER";
    case GL_COLOR_MATERIAL:
        return "GL_COLOR_MATERIAL";
    case GL_FOG:
        return "GL_FOG";
    case GL_FOG_INDEX:
        return "GL_FOG_INDEX";
    case GL_FOG_DENSITY:
        return "GL_FOG_DENSITY";
    case GL_FOG_START:
        return "GL_FOG_START";
    case GL_FOG_END:
        return "GL_FOG_END";
    case GL_FOG_MODE:
        return "GL_FOG_MODE";
    case GL_FOG_COLOR:
        return "GL_FOG_COLOR";
#endif
    case GL_DEPTH_RANGE:
        return "GL_DEPTH_RANGE";
    case GL_DEPTH_TEST:
        return "GL_DEPTH_TEST";
    case GL_DEPTH_WRITEMASK:
        return "GL_DEPTH_WRITEMASK";
    case GL_DEPTH_CLEAR_VALUE:
        return "GL_DEPTH_CLEAR_VALUE";
    case GL_DEPTH_FUNC:
        return "GL_DEPTH_FUNC";
#ifndef GL_ES_VERSION_3_0
    case GL_ACCUM_CLEAR_VALUE:
        return "GL_ACCUM_CLEAR_VALUE";
#endif
    case GL_STENCIL_TEST:
        return "GL_STENCIL_TEST";
    case GL_STENCIL_CLEAR_VALUE:
        return "GL_STENCIL_CLEAR_VALUE";
    case GL_STENCIL_FUNC:
        return "GL_STENCIL_FUNC";
    case GL_STENCIL_VALUE_MASK:
        return "GL_STENCIL_VALUE_MASK";
    case GL_STENCIL_FAIL:
        return "GL_STENCIL_FAIL";
    case GL_STENCIL_PASS_DEPTH_FAIL:
        return "GL_STENCIL_PASS_DEPTH_FAIL";
    case GL_STENCIL_PASS_DEPTH_PASS:
        return "GL_STENCIL_PASS_DEPTH_PASS";
    case GL_STENCIL_REF:
        return "GL_STENCIL_REF";
    case GL_STENCIL_WRITEMASK:
        return "GL_STENCIL_WRITEMASK";
#ifndef GL_ES_VERSION_3_0
    case GL_MATRIX_MODE:
        return "GL_MATRIX_MODE";
    case GL_NORMALIZE:
        return "GL_NORMALIZE";
#endif
    case GL_VIEWPORT:
        return "GL_VIEWPORT";
#ifndef GL_ES_VERSION_3_0
    case GL_MODELVIEW_STACK_DEPTH:
        return "GL_MODELVIEW_STACK_DEPTH";
    case GL_PROJECTION_STACK_DEPTH:
        return "GL_PROJECTION_STACK_DEPTH";
    case GL_TEXTURE_STACK_DEPTH:
        return "GL_TEXTURE_STACK_DEPTH";
    case GL_MODELVIEW_MATRIX:
        return "GL_MODELVIEW_MATRIX";
    case GL_PROJECTION_MATRIX:
        return "GL_PROJECTION_MATRIX";
    case GL_TEXTURE_MATRIX:
        return "GL_TEXTURE_MATRIX";
    case GL_ATTRIB_STACK_DEPTH:
        return "GL_ATTRIB_STACK_DEPTH";
    case GL_CLIENT_ATTRIB_STACK_DEPTH:
        return "GL_CLIENT_ATTRIB_STACK_DEPTH";
    case GL_ALPHA_TEST:
        return "GL_ALPHA_TEST";
    case GL_ALPHA_TEST_FUNC:
        return "GL_ALPHA_TEST_FUNC";
    case GL_ALPHA_TEST_REF:
        return "GL_ALPHA_TEST_REF";
#endif
    case GL_DITHER:
        return "GL_DITHER";
#ifndef GL_ES_VERSION_3_0
    case GL_BLEND_DST:
        return "GL_BLEND_DST";
    case GL_BLEND_SRC:
        return "GL_BLEND_SRC";
#endif
    case GL_BLEND:
        return "GL_BLEND";
#ifndef GL_ES_VERSION_3_0
    case GL_LOGIC_OP_MODE:
        return "GL_LOGIC_OP_MODE";
    case GL_INDEX_LOGIC_OP:
        return "GL_INDEX_LOGIC_OP";
    case GL_COLOR_LOGIC_OP:
        return "GL_COLOR_LOGIC_OP";
    case GL_AUX_BUFFERS:
        return "GL_AUX_BUFFERS";
    case GL_DRAW_BUFFER:
        return "GL_DRAW_BUFFER";
#endif
    case GL_READ_BUFFER:
        return "GL_READ_BUFFER";
    case GL_SCISSOR_BOX:
        return "GL_SCISSOR_BOX";
    case GL_SCISSOR_TEST:
        return "GL_SCISSOR_TEST";
#ifndef GL_ES_VERSION_3_0
    case GL_INDEX_CLEAR_VALUE:
        return "GL_INDEX_CLEAR_VALUE";
    case GL_INDEX_WRITEMASK:
        return "GL_INDEX_WRITEMASK";
#endif
    case GL_COLOR_CLEAR_VALUE:
        return "GL_COLOR_CLEAR_VALUE";
    case GL_COLOR_WRITEMASK:
        return "GL_COLOR_WRITEMASK";
#ifndef GL_ES_VERSION_3_0
    case GL_INDEX_MODE:
        return "GL_INDEX_MODE";
    case GL_RGBA_MODE:
        return "GL_RGBA_MODE";
    case GL_DOUBLEBUFFER:
        return "GL_DOUBLEBUFFER";
    case GL_STEREO:
        return "GL_STEREO";
    case GL_RENDER_MODE:
        return "GL_RENDER_MODE";
    case GL_PERSPECTIVE_CORRECTION_HINT:
        return "GL_PERSPECTIVE_CORRECTION_HINT";
    case GL_POINT_SMOOTH_HINT:
        return "GL_POINT_SMOOTH_HINT";
    case GL_LINE_SMOOTH_HINT:
        return "GL_LINE_SMOOTH_HINT";
    case GL_POLYGON_SMOOTH_HINT:
        return "GL_POLYGON_SMOOTH_HINT";
    case GL_FOG_HINT:
        return "GL_FOG_HINT";
    case GL_TEXTURE_GEN_S:
        return "GL_TEXTURE_GEN_S";
    case GL_TEXTURE_GEN_T:
        return "GL_TEXTURE_GEN_T";
    case GL_TEXTURE_GEN_R:
        return "GL_TEXTURE_GEN_R";
    case GL_TEXTURE_GEN_Q:
        return "GL_TEXTURE_GEN_Q";
    case GL_PIXEL_MAP_I_TO_I:
        return "GL_PIXEL_MAP_I_TO_I";
    case GL_PIXEL_MAP_S_TO_S:
        return "GL_PIXEL_MAP_S_TO_S";
    case GL_PIXEL_MAP_I_TO_R:
        return "GL_PIXEL_MAP_I_TO_R";
    case GL_PIXEL_MAP_I_TO_G:
        return "GL_PIXEL_MAP_I_TO_G";
    case GL_PIXEL_MAP_I_TO_B:
        return "GL_PIXEL_MAP_I_TO_B";
    case GL_PIXEL_MAP_I_TO_A:
        return "GL_PIXEL_MAP_I_TO_A";
    case GL_PIXEL_MAP_R_TO_R:
        return "GL_PIXEL_MAP_R_TO_R";
    case GL_PIXEL_MAP_G_TO_G:
        return "GL_PIXEL_MAP_G_TO_G";
    case GL_PIXEL_MAP_B_TO_B:
        return "GL_PIXEL_MAP_B_TO_B";
    case GL_PIXEL_MAP_A_TO_A:
        return "GL_PIXEL_MAP_A_TO_A";
    case GL_PIXEL_MAP_I_TO_I_SIZE:
        return "GL_PIXEL_MAP_I_TO_I_SIZE";
    case GL_PIXEL_MAP_S_TO_S_SIZE:
        return "GL_PIXEL_MAP_S_TO_S_SIZE";
    case GL_PIXEL_MAP_I_TO_R_SIZE:
        return "GL_PIXEL_MAP_I_TO_R_SIZE";
    case GL_PIXEL_MAP_I_TO_G_SIZE:
        return "GL_PIXEL_MAP_I_TO_G_SIZE";
    case GL_PIXEL_MAP_I_TO_B_SIZE:
        return "GL_PIXEL_MAP_I_TO_B_SIZE";
    case GL_PIXEL_MAP_I_TO_A_SIZE:
        return "GL_PIXEL_MAP_I_TO_A_SIZE";
    case GL_PIXEL_MAP_R_TO_R_SIZE:
        return "GL_PIXEL_MAP_R_TO_R_SIZE";
    case GL_PIXEL_MAP_G_TO_G_SIZE:
        return "GL_PIXEL_MAP_G_TO_G_SIZE";
    case GL_PIXEL_MAP_B_TO_B_SIZE:
        return "GL_PIXEL_MAP_B_TO_B_SIZE";
    case GL_PIXEL_MAP_A_TO_A_SIZE:
        return "GL_PIXEL_MAP_A_TO_A_SIZE";
    case GL_UNPACK_SWAP_BYTES:
        return "GL_UNPACK_SWAP_BYTES";
    case GL_UNPACK_LSB_FIRST:
        return "GL_UNPACK_LSB_FIRST";
    case GL_UNPACK_ROW_LENGTH:
        return "GL_UNPACK_ROW_LENGTH";
    case GL_UNPACK_SKIP_ROWS:
        return "GL_UNPACK_SKIP_ROWS";
    case GL_UNPACK_SKIP_PIXELS:
        return "GL_UNPACK_SKIP_PIXELS";
    case GL_UNPACK_ALIGNMENT:
        return "GL_UNPACK_ALIGNMENT";
    case GL_PACK_SWAP_BYTES:
        return "GL_PACK_SWAP_BYTES";
    case GL_PACK_LSB_FIRST:
        return "GL_PACK_LSB_FIRST";
#endif
    case GL_PACK_ROW_LENGTH:
        return "GL_PACK_ROW_LENGTH";
    case GL_PACK_SKIP_ROWS:
        return "GL_PACK_SKIP_ROWS";
    case GL_PACK_SKIP_PIXELS:
        return "GL_PACK_SKIP_PIXELS";
    case GL_PACK_ALIGNMENT:
        return "GL_PACK_ALIGNMENT";
        #ifndef GL_ES_VERSION_3_0

    case GL_MAP_COLOR:
        return "GL_MAP_COLOR";
    case GL_MAP_STENCIL:
        return "GL_MAP_STENCIL";
    case GL_INDEX_SHIFT:
        return "GL_INDEX_SHIFT";
    case GL_INDEX_OFFSET:
        return "GL_INDEX_OFFSET";
    case GL_RED_SCALE:
        return "GL_RED_SCALE";
    case GL_RED_BIAS:
        return "GL_RED_BIAS";
    case GL_ZOOM_X:
        return "GL_ZOOM_X";
    case GL_ZOOM_Y:
        return "GL_ZOOM_Y";
    case GL_GREEN_SCALE:
        return "GL_GREEN_SCALE";
    case GL_GREEN_BIAS:
        return "GL_GREEN_BIAS";
    case GL_BLUE_SCALE:
        return "GL_BLUE_SCALE";
    case GL_BLUE_BIAS:
        return "GL_BLUE_BIAS";
    case GL_ALPHA_SCALE:
        return "GL_ALPHA_SCALE";
    case GL_ALPHA_BIAS:
        return "GL_ALPHA_BIAS";
    case GL_DEPTH_SCALE:
        return "GL_DEPTH_SCALE";
    case GL_DEPTH_BIAS:
        return "GL_DEPTH_BIAS";
    case GL_MAX_EVAL_ORDER:
        return "GL_MAX_EVAL_ORDER";
    case GL_MAX_LIGHTS:
        return "GL_MAX_LIGHTS";
    case GL_MAX_CLIP_DISTANCES:
        return "GL_MAX_CLIP_DISTANCES";
#endif
    case GL_MAX_TEXTURE_SIZE:
        return "GL_MAX_TEXTURE_SIZE";
#ifndef GL_ES_VERSION_3_0
    case GL_MAX_PIXEL_MAP_TABLE:
        return "GL_MAX_PIXEL_MAP_TABLE";
    case GL_MAX_ATTRIB_STACK_DEPTH:
        return "GL_MAX_ATTRIB_STACK_DEPTH";
    case GL_MAX_MODELVIEW_STACK_DEPTH:
        return "GL_MAX_MODELVIEW_STACK_DEPTH";
    case GL_MAX_NAME_STACK_DEPTH:
        return "GL_MAX_NAME_STACK_DEPTH";
    case GL_MAX_PROJECTION_STACK_DEPTH:
        return "GL_MAX_PROJECTION_STACK_DEPTH";
    case GL_MAX_TEXTURE_STACK_DEPTH:
        return "GL_MAX_TEXTURE_STACK_DEPTH";
#endif
    case GL_MAX_VIEWPORT_DIMS:
        return "GL_MAX_VIEWPORT_DIMS";
#ifndef GL_ES_VERSION_3_0
    case GL_MAX_CLIENT_ATTRIB_STACK_DEPTH:
        return "GL_MAX_CLIENT_ATTRIB_STACK_DEPTH";
#endif
    case GL_SUBPIXEL_BITS:
        return "GL_SUBPIXEL_BITS";
#ifndef GL_ES_VERSION_3_0
    case GL_INDEX_BITS:
        return "GL_INDEX_BITS";
#endif
    case GL_RED_BITS:
        return "GL_RED_BITS";
    case GL_GREEN_BITS:
        return "GL_GREEN_BITS";
    case GL_BLUE_BITS:
        return "GL_BLUE_BITS";
    case GL_ALPHA_BITS:
        return "GL_ALPHA_BITS";
    case GL_DEPTH_BITS:
        return "GL_DEPTH_BITS";
    case GL_STENCIL_BITS:
        return "GL_STENCIL_BITS";
#ifndef GL_ES_VERSION_3_0
    case GL_ACCUM_RED_BITS:
        return "GL_ACCUM_RED_BITS";
    case GL_ACCUM_GREEN_BITS:
        return "GL_ACCUM_GREEN_BITS";
    case GL_ACCUM_BLUE_BITS:
        return "GL_ACCUM_BLUE_BITS";
    case GL_ACCUM_ALPHA_BITS:
        return "GL_ACCUM_ALPHA_BITS";
    case GL_NAME_STACK_DEPTH:
        return "GL_NAME_STACK_DEPTH";
    case GL_AUTO_NORMAL:
        return "GL_AUTO_NORMAL";
    case GL_MAP1_COLOR_4:
        return "GL_MAP1_COLOR_4";
    case GL_MAP1_INDEX:
        return "GL_MAP1_INDEX";
    case GL_MAP1_NORMAL:
        return "GL_MAP1_NORMAL";
    case GL_MAP1_TEXTURE_COORD_1:
        return "GL_MAP1_TEXTURE_COORD_1";
    case GL_MAP1_TEXTURE_COORD_2:
        return "GL_MAP1_TEXTURE_COORD_2";
    case GL_MAP1_TEXTURE_COORD_3:
        return "GL_MAP1_TEXTURE_COORD_3";
    case GL_MAP1_TEXTURE_COORD_4:
        return "GL_MAP1_TEXTURE_COORD_4";
    case GL_MAP1_VERTEX_3:
        return "GL_MAP1_VERTEX_3";
    case GL_MAP1_VERTEX_4:
        return "GL_MAP1_VERTEX_4";
    case GL_MAP2_COLOR_4:
        return "GL_MAP2_COLOR_4";
    case GL_MAP2_INDEX:
        return "GL_MAP2_INDEX";
    case GL_MAP2_NORMAL:
        return "GL_MAP2_NORMAL";
    case GL_MAP2_TEXTURE_COORD_1:
        return "GL_MAP2_TEXTURE_COORD_1";
    case GL_MAP2_TEXTURE_COORD_2:
        return "GL_MAP2_TEXTURE_COORD_2";
    case GL_MAP2_TEXTURE_COORD_3:
        return "GL_MAP2_TEXTURE_COORD_3";
    case GL_MAP2_TEXTURE_COORD_4:
        return "GL_MAP2_TEXTURE_COORD_4";
    case GL_MAP2_VERTEX_3:
        return "GL_MAP2_VERTEX_3";
    case GL_MAP2_VERTEX_4:
        return "GL_MAP2_VERTEX_4";
    case GL_MAP1_GRID_DOMAIN:
        return "GL_MAP1_GRID_DOMAIN";
    case GL_MAP1_GRID_SEGMENTS:
        return "GL_MAP1_GRID_SEGMENTS";
    case GL_MAP2_GRID_DOMAIN:
        return "GL_MAP2_GRID_DOMAIN";
    case GL_MAP2_GRID_SEGMENTS:
        return "GL_MAP2_GRID_SEGMENTS";
    case GL_TEXTURE_1D:
        return "GL_TEXTURE_1D";
#endif
    case GL_TEXTURE_2D:
        return "GL_TEXTURE_2D";
#ifndef GL_ES_VERSION_3_0
    case GL_FEEDBACK_BUFFER_POINTER:
        return "GL_FEEDBACK_BUFFER_POINTER";
    case GL_FEEDBACK_BUFFER_SIZE:
        return "GL_FEEDBACK_BUFFER_SIZE";
    case GL_FEEDBACK_BUFFER_TYPE:
        return "GL_FEEDBACK_BUFFER_TYPE";
    case GL_SELECTION_BUFFER_POINTER:
        return "GL_SELECTION_BUFFER_POINTER";
    case GL_SELECTION_BUFFER_SIZE:
        return "GL_SELECTION_BUFFER_SIZE";
    case GL_TEXTURE_WIDTH:
        return "GL_TEXTURE_WIDTH";
    case GL_TEXTURE_HEIGHT:
        return "GL_TEXTURE_HEIGHT";
    case GL_TEXTURE_INTERNAL_FORMAT:
        return "GL_TEXTURE_INTERNAL_FORMAT";
    case GL_TEXTURE_BORDER_COLOR:
        return "GL_TEXTURE_BORDER_COLOR";
    case GL_TEXTURE_BORDER:
        return "GL_TEXTURE_BORDER";
    case GL_TEXTURE_TARGET:
        return "GL_TEXTURE_TARGET";
#endif
    case GL_DONT_CARE:
        return "GL_DONT_CARE";
    case GL_FASTEST:
        return "GL_FASTEST";
    case GL_NICEST:
        return "GL_NICEST";
#ifndef GL_ES_VERSION_3_0
    case GL_AMBIENT:
        return "GL_AMBIENT";
    case GL_DIFFUSE:
        return "GL_DIFFUSE";
    case GL_SPECULAR:
        return "GL_SPECULAR";
    case GL_POSITION:
        return "GL_POSITION";
    case GL_SPOT_DIRECTION:
        return "GL_SPOT_DIRECTION";
    case GL_SPOT_EXPONENT:
        return "GL_SPOT_EXPONENT";
    case GL_SPOT_CUTOFF:
        return "GL_SPOT_CUTOFF";
    case GL_CONSTANT_ATTENUATION:
        return "GL_CONSTANT_ATTENUATION";
    case GL_LINEAR_ATTENUATION:
        return "GL_LINEAR_ATTENUATION";
    case GL_QUADRATIC_ATTENUATION:
        return "GL_QUADRATIC_ATTENUATION";
    case GL_COMPILE:
        return "GL_COMPILE";
    case GL_COMPILE_AND_EXECUTE:
        return "GL_COMPILE_AND_EXECUTE";
#endif
    case GL_BYTE:
        return "GL_BYTE";
    case GL_UNSIGNED_BYTE:
        return "GL_UNSIGNED_BYTE";
    case GL_SHORT:
        return "GL_SHORT";
    case GL_UNSIGNED_SHORT:
        return "GL_UNSIGNED_SHORT";
    case GL_INT:
        return "GL_INT";
    case GL_UNSIGNED_INT:
        return "GL_UNSIGNED_INT";
    case GL_FLOAT:
        return "GL_FLOAT";
#ifndef GL_ES_VERSION_3_0
    case GL_2_BYTES:
        return "GL_2_BYTES";
    case GL_3_BYTES:
        return "GL_3_BYTES";
    case GL_4_BYTES:
        return "GL_4_BYTES";
    case GL_DOUBLE:
        return "GL_DOUBLE";
    case GL_HALF_FLOAT:
        return "GL_HALF_FLOAT";
#endif
    case GL_FIXED:
        return "GL_FIXED";
#ifndef GL_ES_VERSION_3_0
    case GL_INT64_ARB:
        return "GL_INT64_ARB";
    case GL_UNSIGNED_INT64_ARB:
        return "GL_UNSIGNED_INT64_ARB";
    case GL_CLEAR:
        return "GL_CLEAR";
    case GL_AND:
        return "GL_AND";
    case GL_AND_REVERSE:
        return "GL_AND_REVERSE";
    case GL_COPY:
        return "GL_COPY";
    case GL_AND_INVERTED:
        return "GL_AND_INVERTED";
    case GL_NOOP:
        return "GL_NOOP";
    case GL_XOR:
        return "GL_XOR";
    case GL_OR:
        return "GL_OR";
    case GL_NOR:
        return "GL_NOR";
    case GL_EQUIV:
        return "GL_EQUIV";
#endif
    case GL_INVERT:
        return "GL_INVERT";
#ifndef GL_ES_VERSION_3_0
    case GL_OR_REVERSE:
        return "GL_OR_REVERSE";
    case GL_COPY_INVERTED:
        return "GL_COPY_INVERTED";
    case GL_OR_INVERTED:
        return "GL_OR_INVERTED";
    case GL_NAND:
        return "GL_NAND";
    case GL_SET:
        return "GL_SET";
    case GL_EMISSION:
        return "GL_EMISSION";
    case GL_SHININESS:
        return "GL_SHININESS";
    case GL_AMBIENT_AND_DIFFUSE:
        return "GL_AMBIENT_AND_DIFFUSE";
    case GL_COLOR_INDEXES:
        return "GL_COLOR_INDEXES";
    case GL_MODELVIEW:
        return "GL_MODELVIEW";
    case GL_PROJECTION:
        return "GL_PROJECTION";
#endif
    case GL_TEXTURE:
        return "GL_TEXTURE";
    case GL_COLOR:
        return "GL_COLOR";
    case GL_DEPTH:
        return "GL_DEPTH";
    case GL_STENCIL:
        return "GL_STENCIL";
#ifndef GL_ES_VERSION_3_0
    case GL_COLOR_INDEX:
        return "GL_COLOR_INDEX";
    case GL_STENCIL_INDEX:
        return "GL_STENCIL_INDEX";
#endif
    case GL_DEPTH_COMPONENT:
        return "GL_DEPTH_COMPONENT";
    case GL_RED:
        return "GL_RED";
    case GL_GREEN:
        return "GL_GREEN";
    case GL_BLUE:
        return "GL_BLUE";
    case GL_ALPHA:
        return "GL_ALPHA";
    case GL_RGB:
        return "GL_RGB";
    case GL_RGBA:
        return "GL_RGBA";
    case GL_LUMINANCE:
        return "GL_LUMINANCE";
    case GL_LUMINANCE_ALPHA:
        return "GL_LUMINANCE_ALPHA";
#ifndef GL_ES_VERSION_3_0
    case GL_BITMAP:
        return "GL_BITMAP";
    case GL_POINT:
        return "GL_POINT";
    case GL_LINE:
        return "GL_LINE";
    case GL_FILL:
        return "GL_FILL";
    case GL_RENDER:
        return "GL_RENDER";
    case GL_FEEDBACK:
        return "GL_FEEDBACK";
    case GL_SELECT:
        return "GL_SELECT";
    case GL_FLAT:
        return "GL_FLAT";
    case GL_SMOOTH:
        return "GL_SMOOTH";
#endif
    case GL_KEEP:
        return "GL_KEEP";
    case GL_REPLACE:
        return "GL_REPLACE";
    case GL_INCR:
        return "GL_INCR";
    case GL_DECR:
        return "GL_DECR";
    case GL_VENDOR:
        return "GL_VENDOR";
    case GL_RENDERER:
        return "GL_RENDERER";
    case GL_VERSION:
        return "GL_VERSION";
    case GL_EXTENSIONS:
        return "GL_EXTENSIONS";
#ifndef GL_ES_VERSION_3_0
    case GL_S:
        return "GL_S";
    case GL_T:
        return "GL_T";
    case GL_R:
        return "GL_R";
    case GL_Q:
        return "GL_Q";
    case GL_MODULATE:
        return "GL_MODULATE";
    case GL_DECAL:
        return "GL_DECAL";
    case GL_TEXTURE_ENV_MODE:
        return "GL_TEXTURE_ENV_MODE";
    case GL_TEXTURE_ENV_COLOR:
        return "GL_TEXTURE_ENV_COLOR";
    case GL_TEXTURE_ENV:
        return "GL_TEXTURE_ENV";
    case GL_EYE_LINEAR:
        return "GL_EYE_LINEAR";
    case GL_OBJECT_LINEAR:
        return "GL_OBJECT_LINEAR";
    case GL_SPHERE_MAP:
        return "GL_SPHERE_MAP";
    case GL_TEXTURE_GEN_MODE:
        return "GL_TEXTURE_GEN_MODE";
    case GL_OBJECT_PLANE:
        return "GL_OBJECT_PLANE";
    case GL_EYE_PLANE:
        return "GL_EYE_PLANE";
#endif
    case GL_NEAREST:
        return "GL_NEAREST";
    case GL_LINEAR:
        return "GL_LINEAR";
    case GL_NEAREST_MIPMAP_NEAREST:
        return "GL_NEAREST_MIPMAP_NEAREST";
    case GL_LINEAR_MIPMAP_NEAREST:
        return "GL_LINEAR_MIPMAP_NEAREST";
    case GL_NEAREST_MIPMAP_LINEAR:
        return "GL_NEAREST_MIPMAP_LINEAR";
    case GL_LINEAR_MIPMAP_LINEAR:
        return "GL_LINEAR_MIPMAP_LINEAR";
    case GL_TEXTURE_MAG_FILTER:
        return "GL_TEXTURE_MAG_FILTER";
    case GL_TEXTURE_MIN_FILTER:
        return "GL_TEXTURE_MIN_FILTER";
    case GL_TEXTURE_WRAP_S:
        return "GL_TEXTURE_WRAP_S";
    case GL_TEXTURE_WRAP_T:
        return "GL_TEXTURE_WRAP_T";
#ifndef GL_ES_VERSION_3_0
    case GL_CLAMP:
        return "GL_CLAMP";
#endif
    case GL_REPEAT:
        return "GL_REPEAT";
    case GL_POLYGON_OFFSET_UNITS:
        return "GL_POLYGON_OFFSET_UNITS";
#ifndef GL_ES_VERSION_3_0
    case GL_POLYGON_OFFSET_POINT:
        return "GL_POLYGON_OFFSET_POINT";
    case GL_POLYGON_OFFSET_LINE:
        return "GL_POLYGON_OFFSET_LINE";
    case GL_R3_G3_B2:
        return "GL_R3_G3_B2";
    case GL_V2F:
        return "GL_V2F";
    case GL_V3F:
        return "GL_V3F";
    case GL_C4UB_V2F:
        return "GL_C4UB_V2F";
    case GL_C4UB_V3F:
        return "GL_C4UB_V3F";
    case GL_C3F_V3F:
        return "GL_C3F_V3F";
    case GL_N3F_V3F:
        return "GL_N3F_V3F";
    case GL_C4F_N3F_V3F:
        return "GL_C4F_N3F_V3F";
    case GL_T2F_V3F:
        return "GL_T2F_V3F";
    case GL_T4F_V4F:
        return "GL_T4F_V4F";
    case GL_T2F_C4UB_V3F:
        return "GL_T2F_C4UB_V3F";
    case GL_T2F_C3F_V3F:
        return "GL_T2F_C3F_V3F";
    case GL_T2F_N3F_V3F:
        return "GL_T2F_N3F_V3F";
    case GL_T2F_C4F_N3F_V3F:
        return "GL_T2F_C4F_N3F_V3F";
    case GL_T4F_C4F_N3F_V4F:
        return "GL_T4F_C4F_N3F_V4F";
    case GL_CLIP_DISTANCE0:
        return "GL_CLIP_DISTANCE0";
    case GL_CLIP_DISTANCE1:
        return "GL_CLIP_DISTANCE1";
    case GL_CLIP_DISTANCE2:
        return "GL_CLIP_DISTANCE2";
    case GL_CLIP_DISTANCE3:
        return "GL_CLIP_DISTANCE3";
    case GL_CLIP_DISTANCE4:
        return "GL_CLIP_DISTANCE4";
    case GL_CLIP_DISTANCE5:
        return "GL_CLIP_DISTANCE5";
    case GL_CLIP_DISTANCE6:
        return "GL_CLIP_DISTANCE6";
    case GL_CLIP_DISTANCE7:
        return "GL_CLIP_DISTANCE7";
    case GL_LIGHT0:
        return "GL_LIGHT0";
    case GL_LIGHT1:
        return "GL_LIGHT1";
    case GL_LIGHT2:
        return "GL_LIGHT2";
    case GL_LIGHT3:
        return "GL_LIGHT3";
    case GL_LIGHT4:
        return "GL_LIGHT4";
    case GL_LIGHT5:
        return "GL_LIGHT5";
    case GL_LIGHT6:
        return "GL_LIGHT6";
    case GL_LIGHT7:
        return "GL_LIGHT7";
    case GL_ABGR_EXT:
        return "GL_ABGR_EXT";
#endif
    case GL_CONSTANT_COLOR:
        return "GL_CONSTANT_COLOR";
    case GL_ONE_MINUS_CONSTANT_COLOR:
        return "GL_ONE_MINUS_CONSTANT_COLOR";
    case GL_CONSTANT_ALPHA:
        return "GL_CONSTANT_ALPHA";
    case GL_ONE_MINUS_CONSTANT_ALPHA:
        return "GL_ONE_MINUS_CONSTANT_ALPHA";
    case GL_BLEND_COLOR:
        return "GL_BLEND_COLOR";
    case GL_FUNC_ADD:
        return "GL_FUNC_ADD";
    case GL_MIN:
        return "GL_MIN";
    case GL_MAX:
        return "GL_MAX";
    case GL_BLEND_EQUATION:
        return "GL_BLEND_EQUATION";
    case GL_FUNC_SUBTRACT:
        return "GL_FUNC_SUBTRACT";
    case GL_FUNC_REVERSE_SUBTRACT:
        return "GL_FUNC_REVERSE_SUBTRACT";
#ifndef GL_ES_VERSION_3_0
    case GL_CMYK_EXT:
        return "GL_CMYK_EXT";
    case GL_CMYKA_EXT:
        return "GL_CMYKA_EXT";
    case GL_PACK_CMYK_HINT_EXT:
        return "GL_PACK_CMYK_HINT_EXT";
    case GL_UNPACK_CMYK_HINT_EXT:
        return "GL_UNPACK_CMYK_HINT_EXT";
    case GL_CONVOLUTION_1D:
        return "GL_CONVOLUTION_1D";
    case GL_CONVOLUTION_2D:
        return "GL_CONVOLUTION_2D";
    case GL_SEPARABLE_2D:
        return "GL_SEPARABLE_2D";
    case GL_CONVOLUTION_BORDER_MODE:
        return "GL_CONVOLUTION_BORDER_MODE";
    case GL_CONVOLUTION_FILTER_SCALE:
        return "GL_CONVOLUTION_FILTER_SCALE";
    case GL_CONVOLUTION_FILTER_BIAS:
        return "GL_CONVOLUTION_FILTER_BIAS";
    case GL_REDUCE:
        return "GL_REDUCE";
    case GL_CONVOLUTION_FORMAT:
        return "GL_CONVOLUTION_FORMAT";
    case GL_CONVOLUTION_WIDTH:
        return "GL_CONVOLUTION_WIDTH";
    case GL_CONVOLUTION_HEIGHT:
        return "GL_CONVOLUTION_HEIGHT";
    case GL_MAX_CONVOLUTION_WIDTH:
        return "GL_MAX_CONVOLUTION_WIDTH";
    case GL_MAX_CONVOLUTION_HEIGHT:
        return "GL_MAX_CONVOLUTION_HEIGHT";
    case GL_POST_CONVOLUTION_RED_SCALE:
        return "GL_POST_CONVOLUTION_RED_SCALE";
    case GL_POST_CONVOLUTION_GREEN_SCALE:
        return "GL_POST_CONVOLUTION_GREEN_SCALE";
    case GL_POST_CONVOLUTION_BLUE_SCALE:
        return "GL_POST_CONVOLUTION_BLUE_SCALE";
    case GL_POST_CONVOLUTION_ALPHA_SCALE:
        return "GL_POST_CONVOLUTION_ALPHA_SCALE";
    case GL_POST_CONVOLUTION_RED_BIAS:
        return "GL_POST_CONVOLUTION_RED_BIAS";
    case GL_POST_CONVOLUTION_GREEN_BIAS:
        return "GL_POST_CONVOLUTION_GREEN_BIAS";
    case GL_POST_CONVOLUTION_BLUE_BIAS:
        return "GL_POST_CONVOLUTION_BLUE_BIAS";
    case GL_POST_CONVOLUTION_ALPHA_BIAS:
        return "GL_POST_CONVOLUTION_ALPHA_BIAS";
    case GL_HISTOGRAM:
        return "GL_HISTOGRAM";
    case GL_PROXY_HISTOGRAM:
        return "GL_PROXY_HISTOGRAM";
    case GL_HISTOGRAM_WIDTH:
        return "GL_HISTOGRAM_WIDTH";
    case GL_HISTOGRAM_FORMAT:
        return "GL_HISTOGRAM_FORMAT";
    case GL_HISTOGRAM_RED_SIZE:
        return "GL_HISTOGRAM_RED_SIZE";
    case GL_HISTOGRAM_GREEN_SIZE:
        return "GL_HISTOGRAM_GREEN_SIZE";
    case GL_HISTOGRAM_BLUE_SIZE:
        return "GL_HISTOGRAM_BLUE_SIZE";
    case GL_HISTOGRAM_ALPHA_SIZE:
        return "GL_HISTOGRAM_ALPHA_SIZE";
    case GL_HISTOGRAM_LUMINANCE_SIZE:
        return "GL_HISTOGRAM_LUMINANCE_SIZE";
    case GL_HISTOGRAM_SINK:
        return "GL_HISTOGRAM_SINK";
    case GL_MINMAX:
        return "GL_MINMAX";
    case GL_MINMAX_FORMAT:
        return "GL_MINMAX_FORMAT";
    case GL_MINMAX_SINK:
        return "GL_MINMAX_SINK";
    case GL_TABLE_TOO_LARGE:
        return "GL_TABLE_TOO_LARGE";
    case GL_UNSIGNED_BYTE_3_3_2:
        return "GL_UNSIGNED_BYTE_3_3_2";
#endif
    case GL_UNSIGNED_SHORT_4_4_4_4:
        return "GL_UNSIGNED_SHORT_4_4_4_4";
    case GL_UNSIGNED_SHORT_5_5_5_1:
        return "GL_UNSIGNED_SHORT_5_5_5_1";
#ifndef GL_ES_VERSION_3_0
    case GL_UNSIGNED_INT_8_8_8_8:
        return "GL_UNSIGNED_INT_8_8_8_8";
    case GL_UNSIGNED_INT_10_10_10_2:
        return "GL_UNSIGNED_INT_10_10_10_2";
#endif
    case GL_POLYGON_OFFSET_FILL:
        return "GL_POLYGON_OFFSET_FILL";
    case GL_POLYGON_OFFSET_FACTOR:
        return "GL_POLYGON_OFFSET_FACTOR";
#ifndef GL_ES_VERSION_3_0
    case GL_POLYGON_OFFSET_BIAS_EXT:
        return "GL_POLYGON_OFFSET_BIAS_EXT";
    case GL_RESCALE_NORMAL:
        return "GL_RESCALE_NORMAL";
    case GL_ALPHA4:
        return "GL_ALPHA4";
    case GL_ALPHA8:
        return "GL_ALPHA8";
    case GL_ALPHA12:
        return "GL_ALPHA12";
    case GL_ALPHA16:
        return "GL_ALPHA16";
    case GL_LUMINANCE4:
        return "GL_LUMINANCE4";
    case GL_LUMINANCE8:
        return "GL_LUMINANCE8";
    case GL_LUMINANCE12:
        return "GL_LUMINANCE12";
    case GL_LUMINANCE16:
        return "GL_LUMINANCE16";
    case GL_LUMINANCE4_ALPHA4:
        return "GL_LUMINANCE4_ALPHA4";
    case GL_LUMINANCE6_ALPHA2:
        return "GL_LUMINANCE6_ALPHA2";
    case GL_LUMINANCE8_ALPHA8:
        return "GL_LUMINANCE8_ALPHA8";
    case GL_LUMINANCE12_ALPHA4:
        return "GL_LUMINANCE12_ALPHA4";
    case GL_LUMINANCE12_ALPHA12:
        return "GL_LUMINANCE12_ALPHA12";
    case GL_LUMINANCE16_ALPHA16:
        return "GL_LUMINANCE16_ALPHA16";
    case GL_INTENSITY:
        return "GL_INTENSITY";
    case GL_INTENSITY4:
        return "GL_INTENSITY4";
    case GL_INTENSITY8:
        return "GL_INTENSITY8";
    case GL_INTENSITY12:
        return "GL_INTENSITY12";
    case GL_INTENSITY16:
        return "GL_INTENSITY16";
    case GL_RGB2_EXT:
        return "GL_RGB2_EXT";
    case GL_RGB4:
        return "GL_RGB4";
    case GL_RGB5:
        return "GL_RGB5";
#endif
    case GL_RGB8:
        return "GL_RGB8";
#ifndef GL_ES_VERSION_3_0
    case GL_RGB10:
        return "GL_RGB10";
    case GL_RGB12:
        return "GL_RGB12";
    case GL_RGB16:
        return "GL_RGB16";
    case GL_RGBA2:
        return "GL_RGBA2";
#endif
    case GL_RGBA4:
        return "GL_RGBA4";
    case GL_RGB5_A1:
        return "GL_RGB5_A1";
    case GL_RGBA8:
        return "GL_RGBA8";
    case GL_RGB10_A2:
        return "GL_RGB10_A2";
#ifndef GL_ES_VERSION_3_0
    case GL_RGBA12:
        return "GL_RGBA12";
    case GL_RGBA16:
        return "GL_RGBA16";
    case GL_TEXTURE_RED_SIZE:
        return "GL_TEXTURE_RED_SIZE";
    case GL_TEXTURE_GREEN_SIZE:
        return "GL_TEXTURE_GREEN_SIZE";
    case GL_TEXTURE_BLUE_SIZE:
        return "GL_TEXTURE_BLUE_SIZE";
    case GL_TEXTURE_ALPHA_SIZE:
        return "GL_TEXTURE_ALPHA_SIZE";
    case GL_TEXTURE_LUMINANCE_SIZE:
        return "GL_TEXTURE_LUMINANCE_SIZE";
    case GL_TEXTURE_INTENSITY_SIZE:
        return "GL_TEXTURE_INTENSITY_SIZE";
    case GL_REPLACE_EXT:
        return "GL_REPLACE_EXT";
    case GL_PROXY_TEXTURE_1D:
        return "GL_PROXY_TEXTURE_1D";
    case GL_PROXY_TEXTURE_2D:
        return "GL_PROXY_TEXTURE_2D";
    case GL_TEXTURE_TOO_LARGE_EXT:
        return "GL_TEXTURE_TOO_LARGE_EXT";
    case GL_TEXTURE_PRIORITY:
        return "GL_TEXTURE_PRIORITY";
    case GL_TEXTURE_RESIDENT:
        return "GL_TEXTURE_RESIDENT";
    case GL_TEXTURE_BINDING_1D:
        return "GL_TEXTURE_BINDING_1D";
#endif
    case GL_TEXTURE_BINDING_2D:
        return "GL_TEXTURE_BINDING_2D";
    case GL_TEXTURE_BINDING_3D:
        return "GL_TEXTURE_BINDING_3D";
#ifndef GL_ES_VERSION_3_0
    case GL_PACK_SKIP_IMAGES:
        return "GL_PACK_SKIP_IMAGES";
    case GL_PACK_IMAGE_HEIGHT:
        return "GL_PACK_IMAGE_HEIGHT";
#endif
    case GL_UNPACK_SKIP_IMAGES:
        return "GL_UNPACK_SKIP_IMAGES";
    case GL_UNPACK_IMAGE_HEIGHT:
        return "GL_UNPACK_IMAGE_HEIGHT";
    case GL_TEXTURE_3D:
        return "GL_TEXTURE_3D";
#ifndef GL_ES_VERSION_3_0
    case GL_PROXY_TEXTURE_3D:
        return "GL_PROXY_TEXTURE_3D";
    case GL_TEXTURE_DEPTH:
        return "GL_TEXTURE_DEPTH";
#endif
    case GL_TEXTURE_WRAP_R:
        return "GL_TEXTURE_WRAP_R";
    case GL_MAX_3D_TEXTURE_SIZE:
        return "GL_MAX_3D_TEXTURE_SIZE";
#ifndef GL_ES_VERSION_3_0
    case GL_VERTEX_ARRAY:
        return "GL_VERTEX_ARRAY";
    case GL_NORMAL_ARRAY:
        return "GL_NORMAL_ARRAY";
    case GL_COLOR_ARRAY:
        return "GL_COLOR_ARRAY";
    case GL_INDEX_ARRAY:
        return "GL_INDEX_ARRAY";
    case GL_TEXTURE_COORD_ARRAY:
        return "GL_TEXTURE_COORD_ARRAY";
    case GL_EDGE_FLAG_ARRAY:
        return "GL_EDGE_FLAG_ARRAY";
    case GL_VERTEX_ARRAY_SIZE:
        return "GL_VERTEX_ARRAY_SIZE";
    case GL_VERTEX_ARRAY_TYPE:
        return "GL_VERTEX_ARRAY_TYPE";
    case GL_VERTEX_ARRAY_STRIDE:
        return "GL_VERTEX_ARRAY_STRIDE";
    case GL_VERTEX_ARRAY_COUNT_EXT:
        return "GL_VERTEX_ARRAY_COUNT_EXT";
    case GL_NORMAL_ARRAY_TYPE:
        return "GL_NORMAL_ARRAY_TYPE";
    case GL_NORMAL_ARRAY_STRIDE:
        return "GL_NORMAL_ARRAY_STRIDE";
    case GL_NORMAL_ARRAY_COUNT_EXT:
        return "GL_NORMAL_ARRAY_COUNT_EXT";
    case GL_COLOR_ARRAY_SIZE:
        return "GL_COLOR_ARRAY_SIZE";
    case GL_COLOR_ARRAY_TYPE:
        return "GL_COLOR_ARRAY_TYPE";
    case GL_COLOR_ARRAY_STRIDE:
        return "GL_COLOR_ARRAY_STRIDE";
    case GL_COLOR_ARRAY_COUNT_EXT:
        return "GL_COLOR_ARRAY_COUNT_EXT";
    case GL_INDEX_ARRAY_TYPE:
        return "GL_INDEX_ARRAY_TYPE";
    case GL_INDEX_ARRAY_STRIDE:
        return "GL_INDEX_ARRAY_STRIDE";
    case GL_INDEX_ARRAY_COUNT_EXT:
        return "GL_INDEX_ARRAY_COUNT_EXT";
    case GL_TEXTURE_COORD_ARRAY_SIZE:
        return "GL_TEXTURE_COORD_ARRAY_SIZE";
    case GL_TEXTURE_COORD_ARRAY_TYPE:
        return "GL_TEXTURE_COORD_ARRAY_TYPE";
    case GL_TEXTURE_COORD_ARRAY_STRIDE:
        return "GL_TEXTURE_COORD_ARRAY_STRIDE";
    case GL_TEXTURE_COORD_ARRAY_COUNT_EXT:
        return "GL_TEXTURE_COORD_ARRAY_COUNT_EXT";
    case GL_EDGE_FLAG_ARRAY_STRIDE:
        return "GL_EDGE_FLAG_ARRAY_STRIDE";
    case GL_EDGE_FLAG_ARRAY_COUNT_EXT:
        return "GL_EDGE_FLAG_ARRAY_COUNT_EXT";
    case GL_VERTEX_ARRAY_POINTER:
        return "GL_VERTEX_ARRAY_POINTER";
    case GL_NORMAL_ARRAY_POINTER:
        return "GL_NORMAL_ARRAY_POINTER";
    case GL_COLOR_ARRAY_POINTER:
        return "GL_COLOR_ARRAY_POINTER";
    case GL_INDEX_ARRAY_POINTER:
        return "GL_INDEX_ARRAY_POINTER";
    case GL_TEXTURE_COORD_ARRAY_POINTER:
        return "GL_TEXTURE_COORD_ARRAY_POINTER";
    case GL_EDGE_FLAG_ARRAY_POINTER:
        return "GL_EDGE_FLAG_ARRAY_POINTER";
    case GL_INTERLACE_SGIX:
        return "GL_INTERLACE_SGIX";
    case GL_DETAIL_TEXTURE_2D_SGIS:
        return "GL_DETAIL_TEXTURE_2D_SGIS";
    case GL_DETAIL_TEXTURE_2D_BINDING_SGIS:
        return "GL_DETAIL_TEXTURE_2D_BINDING_SGIS";
    case GL_LINEAR_DETAIL_SGIS:
        return "GL_LINEAR_DETAIL_SGIS";
    case GL_LINEAR_DETAIL_ALPHA_SGIS:
        return "GL_LINEAR_DETAIL_ALPHA_SGIS";
    case GL_LINEAR_DETAIL_COLOR_SGIS:
        return "GL_LINEAR_DETAIL_COLOR_SGIS";
    case GL_DETAIL_TEXTURE_LEVEL_SGIS:
        return "GL_DETAIL_TEXTURE_LEVEL_SGIS";
    case GL_DETAIL_TEXTURE_MODE_SGIS:
        return "GL_DETAIL_TEXTURE_MODE_SGIS";
    case GL_DETAIL_TEXTURE_FUNC_POINTS_SGIS:
        return "GL_DETAIL_TEXTURE_FUNC_POINTS_SGIS";
    case GL_MULTISAMPLE:
        return "GL_MULTISAMPLE";
#endif
    case GL_SAMPLE_ALPHA_TO_COVERAGE:
        return "GL_SAMPLE_ALPHA_TO_COVERAGE";
#ifndef GL_ES_VERSION_3_0
    case GL_SAMPLE_ALPHA_TO_ONE:
        return "GL_SAMPLE_ALPHA_TO_ONE";
#endif
    case GL_SAMPLE_COVERAGE:
        return "GL_SAMPLE_COVERAGE";
#ifndef GL_ES_VERSION_3_0
    case GL_1PASS_EXT:
        return "GL_1PASS_EXT";
    case GL_2PASS_0_EXT:
        return "GL_2PASS_0_EXT";
    case GL_2PASS_1_EXT:
        return "GL_2PASS_1_EXT";
    case GL_4PASS_0_EXT:
        return "GL_4PASS_0_EXT";
    case GL_4PASS_1_EXT:
        return "GL_4PASS_1_EXT";
    case GL_4PASS_2_EXT:
        return "GL_4PASS_2_EXT";
    case GL_4PASS_3_EXT:
        return "GL_4PASS_3_EXT";
#endif
    case GL_SAMPLE_BUFFERS:
        return "GL_SAMPLE_BUFFERS";
    case GL_SAMPLES:
        return "GL_SAMPLES";
    case GL_SAMPLE_COVERAGE_VALUE:
        return "GL_SAMPLE_COVERAGE_VALUE";
    case GL_SAMPLE_COVERAGE_INVERT:
        return "GL_SAMPLE_COVERAGE_INVERT";
#ifndef GL_ES_VERSION_3_0
    case GL_SAMPLE_PATTERN_EXT:
        return "GL_SAMPLE_PATTERN_EXT";
    case GL_LINEAR_SHARPEN_SGIS:
        return "GL_LINEAR_SHARPEN_SGIS";
    case GL_LINEAR_SHARPEN_ALPHA_SGIS:
        return "GL_LINEAR_SHARPEN_ALPHA_SGIS";
    case GL_LINEAR_SHARPEN_COLOR_SGIS:
        return "GL_LINEAR_SHARPEN_COLOR_SGIS";
    case GL_SHARPEN_TEXTURE_FUNC_POINTS_SGIS:
        return "GL_SHARPEN_TEXTURE_FUNC_POINTS_SGIS";
    case GL_COLOR_MATRIX:
        return "GL_COLOR_MATRIX";
    case GL_COLOR_MATRIX_STACK_DEPTH:
        return "GL_COLOR_MATRIX_STACK_DEPTH";
    case GL_MAX_COLOR_MATRIX_STACK_DEPTH:
        return "GL_MAX_COLOR_MATRIX_STACK_DEPTH";
    case GL_POST_COLOR_MATRIX_RED_SCALE:
        return "GL_POST_COLOR_MATRIX_RED_SCALE";
    case GL_POST_COLOR_MATRIX_GREEN_SCALE:
        return "GL_POST_COLOR_MATRIX_GREEN_SCALE";
    case GL_POST_COLOR_MATRIX_BLUE_SCALE:
        return "GL_POST_COLOR_MATRIX_BLUE_SCALE";
    case GL_POST_COLOR_MATRIX_ALPHA_SCALE:
        return "GL_POST_COLOR_MATRIX_ALPHA_SCALE";
    case GL_POST_COLOR_MATRIX_RED_BIAS:
        return "GL_POST_COLOR_MATRIX_RED_BIAS";
    case GL_POST_COLOR_MATRIX_GREEN_BIAS:
        return "GL_POST_COLOR_MATRIX_GREEN_BIAS";
    case GL_POST_COLOR_MATRIX_BLUE_BIAS:
        return "GL_POST_COLOR_MATRIX_BLUE_BIAS";
    case GL_POST_COLOR_MATRIX_ALPHA_BIAS:
        return "GL_POST_COLOR_MATRIX_ALPHA_BIAS";
    case GL_TEXTURE_COLOR_TABLE_SGI:
        return "GL_TEXTURE_COLOR_TABLE_SGI";
    case GL_PROXY_TEXTURE_COLOR_TABLE_SGI:
        return "GL_PROXY_TEXTURE_COLOR_TABLE_SGI";
    case GL_TEXTURE_ENV_BIAS_SGIX:
        return "GL_TEXTURE_ENV_BIAS_SGIX";
    case GL_TEXTURE_COMPARE_FAIL_VALUE_ARB:
        return "GL_TEXTURE_COMPARE_FAIL_VALUE_ARB";
#endif
    case GL_BLEND_DST_RGB:
        return "GL_BLEND_DST_RGB";
    case GL_BLEND_SRC_RGB:
        return "GL_BLEND_SRC_RGB";
    case GL_BLEND_DST_ALPHA:
        return "GL_BLEND_DST_ALPHA";
    case GL_BLEND_SRC_ALPHA:
        return "GL_BLEND_SRC_ALPHA";
#ifndef GL_ES_VERSION_3_0
    case GL_422_EXT:
        return "GL_422_EXT";
    case GL_422_REV_EXT:
        return "GL_422_REV_EXT";
    case GL_422_AVERAGE_EXT:
        return "GL_422_AVERAGE_EXT";
    case GL_422_REV_AVERAGE_EXT:
        return "GL_422_REV_AVERAGE_EXT";
    case GL_COLOR_TABLE:
        return "GL_COLOR_TABLE";
    case GL_POST_CONVOLUTION_COLOR_TABLE:
        return "GL_POST_CONVOLUTION_COLOR_TABLE";
    case GL_POST_COLOR_MATRIX_COLOR_TABLE:
        return "GL_POST_COLOR_MATRIX_COLOR_TABLE";
    case GL_PROXY_COLOR_TABLE:
        return "GL_PROXY_COLOR_TABLE";
    case GL_PROXY_POST_CONVOLUTION_COLOR_TABLE:
        return "GL_PROXY_POST_CONVOLUTION_COLOR_TABLE";
    case GL_PROXY_POST_COLOR_MATRIX_COLOR_TABLE:
        return "GL_PROXY_POST_COLOR_MATRIX_COLOR_TABLE";
    case GL_COLOR_TABLE_SCALE:
        return "GL_COLOR_TABLE_SCALE";
    case GL_COLOR_TABLE_BIAS:
        return "GL_COLOR_TABLE_BIAS";
    case GL_COLOR_TABLE_FORMAT:
        return "GL_COLOR_TABLE_FORMAT";
    case GL_COLOR_TABLE_WIDTH:
        return "GL_COLOR_TABLE_WIDTH";
    case GL_COLOR_TABLE_RED_SIZE:
        return "GL_COLOR_TABLE_RED_SIZE";
    case GL_COLOR_TABLE_GREEN_SIZE:
        return "GL_COLOR_TABLE_GREEN_SIZE";
    case GL_COLOR_TABLE_BLUE_SIZE:
        return "GL_COLOR_TABLE_BLUE_SIZE";
    case GL_COLOR_TABLE_ALPHA_SIZE:
        return "GL_COLOR_TABLE_ALPHA_SIZE";
    case GL_COLOR_TABLE_LUMINANCE_SIZE:
        return "GL_COLOR_TABLE_LUMINANCE_SIZE";
    case GL_COLOR_TABLE_INTENSITY_SIZE:
        return "GL_COLOR_TABLE_INTENSITY_SIZE";
    case GL_BGR:
        return "GL_BGR";
    case GL_BGRA:
        return "GL_BGRA";
    case GL_COLOR_INDEX1_EXT:
        return "GL_COLOR_INDEX1_EXT";
    case GL_COLOR_INDEX2_EXT:
        return "GL_COLOR_INDEX2_EXT";
    case GL_COLOR_INDEX4_EXT:
        return "GL_COLOR_INDEX4_EXT";
    case GL_COLOR_INDEX8_EXT:
        return "GL_COLOR_INDEX8_EXT";
    case GL_COLOR_INDEX12_EXT:
        return "GL_COLOR_INDEX12_EXT";
    case GL_COLOR_INDEX16_EXT:
        return "GL_COLOR_INDEX16_EXT";
#endif
    case GL_MAX_ELEMENTS_VERTICES:
        return "GL_MAX_ELEMENTS_VERTICES";
    case GL_MAX_ELEMENTS_INDICES:
        return "GL_MAX_ELEMENTS_INDICES";
#ifndef GL_ES_VERSION_3_0
    case GL_PHONG_WIN:
        return "GL_PHONG_WIN";
    case GL_PHONG_HINT_WIN:
        return "GL_PHONG_HINT_WIN";
    case GL_FOG_SPECULAR_TEXTURE_WIN:
        return "GL_FOG_SPECULAR_TEXTURE_WIN";
    case GL_TEXTURE_INDEX_SIZE_EXT:
        return "GL_TEXTURE_INDEX_SIZE_EXT";
    case GL_PARAMETER_BUFFER_ARB:
        return "GL_PARAMETER_BUFFER_ARB";
    case GL_PARAMETER_BUFFER_BINDING_ARB:
        return "GL_PARAMETER_BUFFER_BINDING_ARB";
    case GL_CLIP_VOLUME_CLIPPING_HINT_EXT:
        return "GL_CLIP_VOLUME_CLIPPING_HINT_EXT";
    case GL_DUAL_ALPHA4_SGIS:
        return "GL_DUAL_ALPHA4_SGIS";
    case GL_DUAL_ALPHA8_SGIS:
        return "GL_DUAL_ALPHA8_SGIS";
    case GL_DUAL_ALPHA12_SGIS:
        return "GL_DUAL_ALPHA12_SGIS";
    case GL_DUAL_ALPHA16_SGIS:
        return "GL_DUAL_ALPHA16_SGIS";
    case GL_DUAL_LUMINANCE4_SGIS:
        return "GL_DUAL_LUMINANCE4_SGIS";
    case GL_DUAL_LUMINANCE8_SGIS:
        return "GL_DUAL_LUMINANCE8_SGIS";
    case GL_DUAL_LUMINANCE12_SGIS:
        return "GL_DUAL_LUMINANCE12_SGIS";
    case GL_DUAL_LUMINANCE16_SGIS:
        return "GL_DUAL_LUMINANCE16_SGIS";
    case GL_DUAL_INTENSITY4_SGIS:
        return "GL_DUAL_INTENSITY4_SGIS";
    case GL_DUAL_INTENSITY8_SGIS:
        return "GL_DUAL_INTENSITY8_SGIS";
    case GL_DUAL_INTENSITY12_SGIS:
        return "GL_DUAL_INTENSITY12_SGIS";
    case GL_DUAL_INTENSITY16_SGIS:
        return "GL_DUAL_INTENSITY16_SGIS";
    case GL_DUAL_LUMINANCE_ALPHA4_SGIS:
        return "GL_DUAL_LUMINANCE_ALPHA4_SGIS";
    case GL_DUAL_LUMINANCE_ALPHA8_SGIS:
        return "GL_DUAL_LUMINANCE_ALPHA8_SGIS";
    case GL_QUAD_ALPHA4_SGIS:
        return "GL_QUAD_ALPHA4_SGIS";
    case GL_QUAD_ALPHA8_SGIS:
        return "GL_QUAD_ALPHA8_SGIS";
    case GL_QUAD_LUMINANCE4_SGIS:
        return "GL_QUAD_LUMINANCE4_SGIS";
    case GL_QUAD_LUMINANCE8_SGIS:
        return "GL_QUAD_LUMINANCE8_SGIS";
    case GL_QUAD_INTENSITY4_SGIS:
        return "GL_QUAD_INTENSITY4_SGIS";
    case GL_QUAD_INTENSITY8_SGIS:
        return "GL_QUAD_INTENSITY8_SGIS";
    case GL_DUAL_TEXTURE_SELECT_SGIS:
        return "GL_DUAL_TEXTURE_SELECT_SGIS";
    case GL_QUAD_TEXTURE_SELECT_SGIS:
        return "GL_QUAD_TEXTURE_SELECT_SGIS";
    case GL_POINT_SIZE_MIN:
        return "GL_POINT_SIZE_MIN";
    case GL_POINT_SIZE_MAX:
        return "GL_POINT_SIZE_MAX";
    case GL_POINT_FADE_THRESHOLD_SIZE:
        return "GL_POINT_FADE_THRESHOLD_SIZE";
    case GL_POINT_DISTANCE_ATTENUATION:
        return "GL_POINT_DISTANCE_ATTENUATION";
    case GL_FOG_FUNC_SGIS:
        return "GL_FOG_FUNC_SGIS";
    case GL_FOG_FUNC_POINTS_SGIS:
        return "GL_FOG_FUNC_POINTS_SGIS";
    case GL_MAX_FOG_FUNC_POINTS_SGIS:
        return "GL_MAX_FOG_FUNC_POINTS_SGIS";
    case GL_CLAMP_TO_BORDER:
        return "GL_CLAMP_TO_BORDER";
    case GL_TEXTURE_MULTI_BUFFER_HINT_SGIX:
        return "GL_TEXTURE_MULTI_BUFFER_HINT_SGIX";
#endif
    case GL_CLAMP_TO_EDGE:
        return "GL_CLAMP_TO_EDGE";
#ifndef GL_ES_VERSION_3_0
    case GL_PACK_SKIP_VOLUMES_SGIS:
        return "GL_PACK_SKIP_VOLUMES_SGIS";
    case GL_PACK_IMAGE_DEPTH_SGIS:
        return "GL_PACK_IMAGE_DEPTH_SGIS";
    case GL_UNPACK_SKIP_VOLUMES_SGIS:
        return "GL_UNPACK_SKIP_VOLUMES_SGIS";
    case GL_UNPACK_IMAGE_DEPTH_SGIS:
        return "GL_UNPACK_IMAGE_DEPTH_SGIS";
    case GL_TEXTURE_4D_SGIS:
        return "GL_TEXTURE_4D_SGIS";
    case GL_PROXY_TEXTURE_4D_SGIS:
        return "GL_PROXY_TEXTURE_4D_SGIS";
    case GL_TEXTURE_4DSIZE_SGIS:
        return "GL_TEXTURE_4DSIZE_SGIS";
    case GL_TEXTURE_WRAP_Q_SGIS:
        return "GL_TEXTURE_WRAP_Q_SGIS";
    case GL_MAX_4D_TEXTURE_SIZE_SGIS:
        return "GL_MAX_4D_TEXTURE_SIZE_SGIS";
    case GL_PIXEL_TEX_GEN_SGIX:
        return "GL_PIXEL_TEX_GEN_SGIX";
#endif
    case GL_TEXTURE_MIN_LOD:
        return "GL_TEXTURE_MIN_LOD";
    case GL_TEXTURE_MAX_LOD:
        return "GL_TEXTURE_MAX_LOD";
    case GL_TEXTURE_BASE_LEVEL:
        return "GL_TEXTURE_BASE_LEVEL";
    case GL_TEXTURE_MAX_LEVEL:
        return "GL_TEXTURE_MAX_LEVEL";
#ifndef GL_ES_VERSION_3_0
    case GL_PIXEL_TILE_BEST_ALIGNMENT_SGIX:
        return "GL_PIXEL_TILE_BEST_ALIGNMENT_SGIX";
    case GL_PIXEL_TILE_CACHE_INCREMENT_SGIX:
        return "GL_PIXEL_TILE_CACHE_INCREMENT_SGIX";
    case GL_PIXEL_TILE_WIDTH_SGIX:
        return "GL_PIXEL_TILE_WIDTH_SGIX";
    case GL_PIXEL_TILE_HEIGHT_SGIX:
        return "GL_PIXEL_TILE_HEIGHT_SGIX";
    case GL_PIXEL_TILE_GRID_WIDTH_SGIX:
        return "GL_PIXEL_TILE_GRID_WIDTH_SGIX";
    case GL_PIXEL_TILE_GRID_HEIGHT_SGIX:
        return "GL_PIXEL_TILE_GRID_HEIGHT_SGIX";
    case GL_PIXEL_TILE_GRID_DEPTH_SGIX:
        return "GL_PIXEL_TILE_GRID_DEPTH_SGIX";
    case GL_PIXEL_TILE_CACHE_SIZE_SGIX:
        return "GL_PIXEL_TILE_CACHE_SIZE_SGIX";
    case GL_FILTER4_SGIS:
        return "GL_FILTER4_SGIS";
    case GL_TEXTURE_FILTER4_SIZE_SGIS:
        return "GL_TEXTURE_FILTER4_SIZE_SGIS";
    case GL_SPRITE_SGIX:
        return "GL_SPRITE_SGIX";
    case GL_SPRITE_MODE_SGIX:
        return "GL_SPRITE_MODE_SGIX";
    case GL_SPRITE_AXIS_SGIX:
        return "GL_SPRITE_AXIS_SGIX";
    case GL_SPRITE_TRANSLATION_SGIX:
        return "GL_SPRITE_TRANSLATION_SGIX";
    case GL_SPRITE_AXIAL_SGIX:
        return "GL_SPRITE_AXIAL_SGIX";
    case GL_SPRITE_OBJECT_ALIGNED_SGIX:
        return "GL_SPRITE_OBJECT_ALIGNED_SGIX";
    case GL_SPRITE_EYE_ALIGNED_SGIX:
        return "GL_SPRITE_EYE_ALIGNED_SGIX";
    case GL_TEXTURE_4D_BINDING_SGIS:
        return "GL_TEXTURE_4D_BINDING_SGIS";
    case GL_IGNORE_BORDER_HP:
        return "GL_IGNORE_BORDER_HP";
    case GL_CONSTANT_BORDER:
        return "GL_CONSTANT_BORDER";
    case GL_REPLICATE_BORDER:
        return "GL_REPLICATE_BORDER";
    case GL_CONVOLUTION_BORDER_COLOR:
        return "GL_CONVOLUTION_BORDER_COLOR";
    case GL_IMAGE_SCALE_X_HP:
        return "GL_IMAGE_SCALE_X_HP";
    case GL_IMAGE_SCALE_Y_HP:
        return "GL_IMAGE_SCALE_Y_HP";
    case GL_IMAGE_TRANSLATE_X_HP:
        return "GL_IMAGE_TRANSLATE_X_HP";
    case GL_IMAGE_TRANSLATE_Y_HP:
        return "GL_IMAGE_TRANSLATE_Y_HP";
    case GL_IMAGE_ROTATE_ANGLE_HP:
        return "GL_IMAGE_ROTATE_ANGLE_HP";
    case GL_IMAGE_ROTATE_ORIGIN_X_HP:
        return "GL_IMAGE_ROTATE_ORIGIN_X_HP";
    case GL_IMAGE_ROTATE_ORIGIN_Y_HP:
        return "GL_IMAGE_ROTATE_ORIGIN_Y_HP";
    case GL_IMAGE_MAG_FILTER_HP:
        return "GL_IMAGE_MAG_FILTER_HP";
    case GL_IMAGE_MIN_FILTER_HP:
        return "GL_IMAGE_MIN_FILTER_HP";
    case GL_IMAGE_CUBIC_WEIGHT_HP:
        return "GL_IMAGE_CUBIC_WEIGHT_HP";
    case GL_CUBIC_HP:
        return "GL_CUBIC_HP";
    case GL_AVERAGE_HP:
        return "GL_AVERAGE_HP";
    case GL_IMAGE_TRANSFORM_2D_HP:
        return "GL_IMAGE_TRANSFORM_2D_HP";
    case GL_POST_IMAGE_TRANSFORM_COLOR_TABLE_HP:
        return "GL_POST_IMAGE_TRANSFORM_COLOR_TABLE_HP";
    case GL_PROXY_POST_IMAGE_TRANSFORM_COLOR_TABLE_HP:
        return "GL_PROXY_POST_IMAGE_TRANSFORM_COLOR_TABLE_HP";
    case GL_OCCLUSION_TEST_HP:
        return "GL_OCCLUSION_TEST_HP";
    case GL_OCCLUSION_TEST_RESULT_HP:
        return "GL_OCCLUSION_TEST_RESULT_HP";
    case GL_TEXTURE_LIGHTING_MODE_HP:
        return "GL_TEXTURE_LIGHTING_MODE_HP";
    case GL_TEXTURE_POST_SPECULAR_HP:
        return "GL_TEXTURE_POST_SPECULAR_HP";
    case GL_TEXTURE_PRE_SPECULAR_HP:
        return "GL_TEXTURE_PRE_SPECULAR_HP";
    case GL_LINEAR_CLIPMAP_LINEAR_SGIX:
        return "GL_LINEAR_CLIPMAP_LINEAR_SGIX";
    case GL_TEXTURE_CLIPMAP_CENTER_SGIX:
        return "GL_TEXTURE_CLIPMAP_CENTER_SGIX";
    case GL_TEXTURE_CLIPMAP_FRAME_SGIX:
        return "GL_TEXTURE_CLIPMAP_FRAME_SGIX";
    case GL_TEXTURE_CLIPMAP_OFFSET_SGIX:
        return "GL_TEXTURE_CLIPMAP_OFFSET_SGIX";
    case GL_TEXTURE_CLIPMAP_VIRTUAL_DEPTH_SGIX:
        return "GL_TEXTURE_CLIPMAP_VIRTUAL_DEPTH_SGIX";
    case GL_TEXTURE_CLIPMAP_LOD_OFFSET_SGIX:
        return "GL_TEXTURE_CLIPMAP_LOD_OFFSET_SGIX";
    case GL_TEXTURE_CLIPMAP_DEPTH_SGIX:
        return "GL_TEXTURE_CLIPMAP_DEPTH_SGIX";
    case GL_MAX_CLIPMAP_DEPTH_SGIX:
        return "GL_MAX_CLIPMAP_DEPTH_SGIX";
    case GL_MAX_CLIPMAP_VIRTUAL_DEPTH_SGIX:
        return "GL_MAX_CLIPMAP_VIRTUAL_DEPTH_SGIX";
    case GL_POST_TEXTURE_FILTER_BIAS_SGIX:
        return "GL_POST_TEXTURE_FILTER_BIAS_SGIX";
    case GL_POST_TEXTURE_FILTER_SCALE_SGIX:
        return "GL_POST_TEXTURE_FILTER_SCALE_SGIX";
    case GL_POST_TEXTURE_FILTER_BIAS_RANGE_SGIX:
        return "GL_POST_TEXTURE_FILTER_BIAS_RANGE_SGIX";
    case GL_POST_TEXTURE_FILTER_SCALE_RANGE_SGIX:
        return "GL_POST_TEXTURE_FILTER_SCALE_RANGE_SGIX";
    case GL_REFERENCE_PLANE_SGIX:
        return "GL_REFERENCE_PLANE_SGIX";
    case GL_REFERENCE_PLANE_EQUATION_SGIX:
        return "GL_REFERENCE_PLANE_EQUATION_SGIX";
    case GL_IR_INSTRUMENT1_SGIX:
        return "GL_IR_INSTRUMENT1_SGIX";
    case GL_INSTRUMENT_BUFFER_POINTER_SGIX:
        return "GL_INSTRUMENT_BUFFER_POINTER_SGIX";
    case GL_INSTRUMENT_MEASUREMENTS_SGIX:
        return "GL_INSTRUMENT_MEASUREMENTS_SGIX";
    case GL_LIST_PRIORITY_SGIX:
        return "GL_LIST_PRIORITY_SGIX";
    case GL_CALLIGRAPHIC_FRAGMENT_SGIX:
        return "GL_CALLIGRAPHIC_FRAGMENT_SGIX";
    case GL_PIXEL_TEX_GEN_Q_CEILING_SGIX:
        return "GL_PIXEL_TEX_GEN_Q_CEILING_SGIX";
    case GL_PIXEL_TEX_GEN_Q_ROUND_SGIX:
        return "GL_PIXEL_TEX_GEN_Q_ROUND_SGIX";
    case GL_PIXEL_TEX_GEN_Q_FLOOR_SGIX:
        return "GL_PIXEL_TEX_GEN_Q_FLOOR_SGIX";
    case GL_PIXEL_TEX_GEN_ALPHA_REPLACE_SGIX:
        return "GL_PIXEL_TEX_GEN_ALPHA_REPLACE_SGIX";
    case GL_PIXEL_TEX_GEN_ALPHA_NO_REPLACE_SGIX:
        return "GL_PIXEL_TEX_GEN_ALPHA_NO_REPLACE_SGIX";
    case GL_PIXEL_TEX_GEN_ALPHA_LS_SGIX:
        return "GL_PIXEL_TEX_GEN_ALPHA_LS_SGIX";
    case GL_PIXEL_TEX_GEN_ALPHA_MS_SGIX:
        return "GL_PIXEL_TEX_GEN_ALPHA_MS_SGIX";
    case GL_FRAMEZOOM_SGIX:
        return "GL_FRAMEZOOM_SGIX";
    case GL_FRAMEZOOM_FACTOR_SGIX:
        return "GL_FRAMEZOOM_FACTOR_SGIX";
    case GL_MAX_FRAMEZOOM_FACTOR_SGIX:
        return "GL_MAX_FRAMEZOOM_FACTOR_SGIX";
    case GL_TEXTURE_LOD_BIAS_S_SGIX:
        return "GL_TEXTURE_LOD_BIAS_S_SGIX";
    case GL_TEXTURE_LOD_BIAS_T_SGIX:
        return "GL_TEXTURE_LOD_BIAS_T_SGIX";
    case GL_TEXTURE_LOD_BIAS_R_SGIX:
        return "GL_TEXTURE_LOD_BIAS_R_SGIX";
    case GL_GENERATE_MIPMAP:
        return "GL_GENERATE_MIPMAP";
#endif
    case GL_GENERATE_MIPMAP_HINT:
        return "GL_GENERATE_MIPMAP_HINT";
#ifndef GL_ES_VERSION_3_0
    case GL_GEOMETRY_DEFORMATION_SGIX:
        return "GL_GEOMETRY_DEFORMATION_SGIX";
    case GL_TEXTURE_DEFORMATION_SGIX:
        return "GL_TEXTURE_DEFORMATION_SGIX";
    case GL_DEFORMATIONS_MASK_SGIX:
        return "GL_DEFORMATIONS_MASK_SGIX";
    case GL_MAX_DEFORMATION_ORDER_SGIX:
        return "GL_MAX_DEFORMATION_ORDER_SGIX";
    case GL_FOG_OFFSET_SGIX:
        return "GL_FOG_OFFSET_SGIX";
    case GL_FOG_OFFSET_VALUE_SGIX:
        return "GL_FOG_OFFSET_VALUE_SGIX";
    case GL_TEXTURE_COMPARE_SGIX:
        return "GL_TEXTURE_COMPARE_SGIX";
    case GL_TEXTURE_COMPARE_OPERATOR_SGIX:
        return "GL_TEXTURE_COMPARE_OPERATOR_SGIX";
    case GL_TEXTURE_LEQUAL_R_SGIX:
        return "GL_TEXTURE_LEQUAL_R_SGIX";
    case GL_TEXTURE_GEQUAL_R_SGIX:
        return "GL_TEXTURE_GEQUAL_R_SGIX";
#endif
    case GL_DEPTH_COMPONENT16:
        return "GL_DEPTH_COMPONENT16";
    case GL_DEPTH_COMPONENT24:
        return "GL_DEPTH_COMPONENT24";
#ifndef GL_ES_VERSION_3_0
    case GL_DEPTH_COMPONENT32:
        return "GL_DEPTH_COMPONENT32";
    case GL_ARRAY_ELEMENT_LOCK_FIRST_EXT:
        return "GL_ARRAY_ELEMENT_LOCK_FIRST_EXT";
    case GL_ARRAY_ELEMENT_LOCK_COUNT_EXT:
        return "GL_ARRAY_ELEMENT_LOCK_COUNT_EXT";
    case GL_CULL_VERTEX_EXT:
        return "GL_CULL_VERTEX_EXT";
    case GL_CULL_VERTEX_EYE_POSITION_EXT:
        return "GL_CULL_VERTEX_EYE_POSITION_EXT";
    case GL_CULL_VERTEX_OBJECT_POSITION_EXT:
        return "GL_CULL_VERTEX_OBJECT_POSITION_EXT";
    case GL_IUI_V2F_EXT:
        return "GL_IUI_V2F_EXT";
    case GL_IUI_V3F_EXT:
        return "GL_IUI_V3F_EXT";
    case GL_IUI_N3F_V2F_EXT:
        return "GL_IUI_N3F_V2F_EXT";
    case GL_IUI_N3F_V3F_EXT:
        return "GL_IUI_N3F_V3F_EXT";
    case GL_T2F_IUI_V2F_EXT:
        return "GL_T2F_IUI_V2F_EXT";
    case GL_T2F_IUI_V3F_EXT:
        return "GL_T2F_IUI_V3F_EXT";
    case GL_T2F_IUI_N3F_V2F_EXT:
        return "GL_T2F_IUI_N3F_V2F_EXT";
    case GL_T2F_IUI_N3F_V3F_EXT:
        return "GL_T2F_IUI_N3F_V3F_EXT";
    case GL_INDEX_TEST_EXT:
        return "GL_INDEX_TEST_EXT";
    case GL_INDEX_TEST_FUNC_EXT:
        return "GL_INDEX_TEST_FUNC_EXT";
    case GL_INDEX_TEST_REF_EXT:
        return "GL_INDEX_TEST_REF_EXT";
    case GL_INDEX_MATERIAL_EXT:
        return "GL_INDEX_MATERIAL_EXT";
    case GL_INDEX_MATERIAL_PARAMETER_EXT:
        return "GL_INDEX_MATERIAL_PARAMETER_EXT";
    case GL_INDEX_MATERIAL_FACE_EXT:
        return "GL_INDEX_MATERIAL_FACE_EXT";
    case GL_YCRCB_422_SGIX:
        return "GL_YCRCB_422_SGIX";
    case GL_YCRCB_444_SGIX:
        return "GL_YCRCB_444_SGIX";
    case GL_WRAP_BORDER_SUN:
        return "GL_WRAP_BORDER_SUN";
    case GL_UNPACK_CONSTANT_DATA_SUNX:
        return "GL_UNPACK_CONSTANT_DATA_SUNX";
    case GL_TEXTURE_CONSTANT_DATA_SUNX:
        return "GL_TEXTURE_CONSTANT_DATA_SUNX";
    case GL_TRIANGLE_LIST_SUN:
        return "GL_TRIANGLE_LIST_SUN";
    case GL_REPLACEMENT_CODE_SUN:
        return "GL_REPLACEMENT_CODE_SUN";
    case GL_GLOBAL_ALPHA_SUN:
        return "GL_GLOBAL_ALPHA_SUN";
    case GL_GLOBAL_ALPHA_FACTOR_SUN:
        return "GL_GLOBAL_ALPHA_FACTOR_SUN";
    case GL_TEXTURE_COLOR_WRITEMASK_SGIS:
        return "GL_TEXTURE_COLOR_WRITEMASK_SGIS";
    case GL_EYE_DISTANCE_TO_POINT_SGIS:
        return "GL_EYE_DISTANCE_TO_POINT_SGIS";
    case GL_OBJECT_DISTANCE_TO_POINT_SGIS:
        return "GL_OBJECT_DISTANCE_TO_POINT_SGIS";
    case GL_EYE_DISTANCE_TO_LINE_SGIS:
        return "GL_EYE_DISTANCE_TO_LINE_SGIS";
    case GL_OBJECT_DISTANCE_TO_LINE_SGIS:
        return "GL_OBJECT_DISTANCE_TO_LINE_SGIS";
    case GL_EYE_POINT_SGIS:
        return "GL_EYE_POINT_SGIS";
    case GL_OBJECT_POINT_SGIS:
        return "GL_OBJECT_POINT_SGIS";
    case GL_EYE_LINE_SGIS:
        return "GL_EYE_LINE_SGIS";
    case GL_OBJECT_LINE_SGIS:
        return "GL_OBJECT_LINE_SGIS";
    case GL_LIGHT_MODEL_COLOR_CONTROL:
        return "GL_LIGHT_MODEL_COLOR_CONTROL";
    case GL_SINGLE_COLOR:
        return "GL_SINGLE_COLOR";
    case GL_SEPARATE_SPECULAR_COLOR:
        return "GL_SEPARATE_SPECULAR_COLOR";
    case GL_SHARED_TEXTURE_PALETTE_EXT:
        return "GL_SHARED_TEXTURE_PALETTE_EXT";
    case GL_FOG_SCALE_SGIX:
        return "GL_FOG_SCALE_SGIX";
    case GL_FOG_SCALE_VALUE_SGIX:
        return "GL_FOG_SCALE_VALUE_SGIX";
    case GL_TEXT_FRAGMENT_SHADER_ATI:
        return "GL_TEXT_FRAGMENT_SHADER_ATI";
#endif
    case GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING:
        return "GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING";
    case GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE:
        return "GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE";
    case GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE:
        return "GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE";
    case GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE:
        return "GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE";
    case GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE:
        return "GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE";
    case GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE:
        return "GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE";
    case GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE:
        return "GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE";
    case GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE:
        return "GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE";
    case GL_FRAMEBUFFER_DEFAULT:
        return "GL_FRAMEBUFFER_DEFAULT";
    case GL_FRAMEBUFFER_UNDEFINED:
        return "GL_FRAMEBUFFER_UNDEFINED";
    case GL_DEPTH_STENCIL_ATTACHMENT:
        return "GL_DEPTH_STENCIL_ATTACHMENT";
    case GL_MAJOR_VERSION:
        return "GL_MAJOR_VERSION";
    case GL_MINOR_VERSION:
        return "GL_MINOR_VERSION";
    case GL_NUM_EXTENSIONS:
        return "GL_NUM_EXTENSIONS";
#ifndef GL_ES_VERSION_3_0
    case GL_CONTEXT_FLAGS:
        return "GL_CONTEXT_FLAGS";
    case GL_BUFFER_IMMUTABLE_STORAGE:
        return "GL_BUFFER_IMMUTABLE_STORAGE";
    case GL_BUFFER_STORAGE_FLAGS:
        return "GL_BUFFER_STORAGE_FLAGS";
#endif
    case GL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED:
        return "GL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED";
#ifndef GL_ES_VERSION_3_0
    case GL_INDEX:
        return "GL_INDEX";
    case GL_COMPRESSED_RED:
        return "GL_COMPRESSED_RED";
    case GL_COMPRESSED_RG:
        return "GL_COMPRESSED_RG";
#endif
    case GL_RG:
        return "GL_RG";
    case GL_RG_INTEGER:
        return "GL_RG_INTEGER";
    case GL_R8:
        return "GL_R8";
#ifndef GL_ES_VERSION_3_0
    case GL_R16:
        return "GL_R16";
#endif
    case GL_RG8:
        return "GL_RG8";
#ifndef GL_ES_VERSION_3_0
    case GL_RG16:
        return "GL_RG16";
#endif
    case GL_R16F:
        return "GL_R16F";
    case GL_R32F:
        return "GL_R32F";
    case GL_RG16F:
        return "GL_RG16F";
    case GL_RG32F:
        return "GL_RG32F";
    case GL_R8I:
        return "GL_R8I";
    case GL_R8UI:
        return "GL_R8UI";
    case GL_R16I:
        return "GL_R16I";
    case GL_R16UI:
        return "GL_R16UI";
    case GL_R32I:
        return "GL_R32I";
    case GL_R32UI:
        return "GL_R32UI";
    case GL_RG8I:
        return "GL_RG8I";
    case GL_RG8UI:
        return "GL_RG8UI";
    case GL_RG16I:
        return "GL_RG16I";
    case GL_RG16UI:
        return "GL_RG16UI";
    case GL_RG32I:
        return "GL_RG32I";
    case GL_RG32UI:
        return "GL_RG32UI";
#ifndef GL_ES_VERSION_3_0
    case GL_SYNC_CL_EVENT_ARB:
        return "GL_SYNC_CL_EVENT_ARB";
    case GL_SYNC_CL_EVENT_COMPLETE_ARB:
        return "GL_SYNC_CL_EVENT_COMPLETE_ARB";
    case GL_DEBUG_OUTPUT_SYNCHRONOUS:
        return "GL_DEBUG_OUTPUT_SYNCHRONOUS";
    case GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH:
        return "GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH";
    case GL_DEBUG_CALLBACK_FUNCTION:
        return "GL_DEBUG_CALLBACK_FUNCTION";
    case GL_DEBUG_CALLBACK_USER_PARAM:
        return "GL_DEBUG_CALLBACK_USER_PARAM";
    case GL_DEBUG_SOURCE_API:
        return "GL_DEBUG_SOURCE_API";
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        return "GL_DEBUG_SOURCE_WINDOW_SYSTEM";
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
        return "GL_DEBUG_SOURCE_SHADER_COMPILER";
    case GL_DEBUG_SOURCE_THIRD_PARTY:
        return "GL_DEBUG_SOURCE_THIRD_PARTY";
    case GL_DEBUG_SOURCE_APPLICATION:
        return "GL_DEBUG_SOURCE_APPLICATION";
    case GL_DEBUG_SOURCE_OTHER:
        return "GL_DEBUG_SOURCE_OTHER";
    case GL_DEBUG_TYPE_ERROR:
        return "GL_DEBUG_TYPE_ERROR";
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        return "GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR";
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        return "GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR";
    case GL_DEBUG_TYPE_PORTABILITY:
        return "GL_DEBUG_TYPE_PORTABILITY";
    case GL_DEBUG_TYPE_PERFORMANCE:
        return "GL_DEBUG_TYPE_PERFORMANCE";
    case GL_DEBUG_TYPE_OTHER:
        return "GL_DEBUG_TYPE_OTHER";
    case GL_LOSE_CONTEXT_ON_RESET:
        return "GL_LOSE_CONTEXT_ON_RESET";
    case GL_GUILTY_CONTEXT_RESET:
        return "GL_GUILTY_CONTEXT_RESET";
    case GL_INNOCENT_CONTEXT_RESET:
        return "GL_INNOCENT_CONTEXT_RESET";
    case GL_UNKNOWN_CONTEXT_RESET:
        return "GL_UNKNOWN_CONTEXT_RESET";
    case GL_RESET_NOTIFICATION_STRATEGY:
        return "GL_RESET_NOTIFICATION_STRATEGY";
#endif
    case GL_PROGRAM_BINARY_RETRIEVABLE_HINT:
        return "GL_PROGRAM_BINARY_RETRIEVABLE_HINT";
#ifndef GL_ES_VERSION_3_0
    case GL_PROGRAM_SEPARABLE:
        return "GL_PROGRAM_SEPARABLE";
    case GL_ACTIVE_PROGRAM:
        return "GL_ACTIVE_PROGRAM";
    case GL_PROGRAM_PIPELINE_BINDING:
        return "GL_PROGRAM_PIPELINE_BINDING";
    case GL_MAX_VIEWPORTS:
        return "GL_MAX_VIEWPORTS";
    case GL_VIEWPORT_SUBPIXEL_BITS:
        return "GL_VIEWPORT_SUBPIXEL_BITS";
    case GL_VIEWPORT_BOUNDS_RANGE:
        return "GL_VIEWPORT_BOUNDS_RANGE";
    case GL_LAYER_PROVOKING_VERTEX:
        return "GL_LAYER_PROVOKING_VERTEX";
    case GL_VIEWPORT_INDEX_PROVOKING_VERTEX:
        return "GL_VIEWPORT_INDEX_PROVOKING_VERTEX";
    case GL_UNDEFINED_VERTEX:
        return "GL_UNDEFINED_VERTEX";
    case GL_NO_RESET_NOTIFICATION:
        return "GL_NO_RESET_NOTIFICATION";
    case GL_MAX_COMPUTE_SHARED_MEMORY_SIZE:
        return "GL_MAX_COMPUTE_SHARED_MEMORY_SIZE";
    case GL_MAX_COMPUTE_UNIFORM_COMPONENTS:
        return "GL_MAX_COMPUTE_UNIFORM_COMPONENTS";
    case GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS:
        return "GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS";
    case GL_MAX_COMPUTE_ATOMIC_COUNTERS:
        return "GL_MAX_COMPUTE_ATOMIC_COUNTERS";
    case GL_MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS:
        return "GL_MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS";
    case GL_COMPUTE_WORK_GROUP_SIZE:
        return "GL_COMPUTE_WORK_GROUP_SIZE";
    case GL_DEBUG_TYPE_MARKER:
        return "GL_DEBUG_TYPE_MARKER";
    case GL_DEBUG_TYPE_PUSH_GROUP:
        return "GL_DEBUG_TYPE_PUSH_GROUP";
    case GL_DEBUG_TYPE_POP_GROUP:
        return "GL_DEBUG_TYPE_POP_GROUP";
    case GL_DEBUG_SEVERITY_NOTIFICATION:
        return "GL_DEBUG_SEVERITY_NOTIFICATION";
    case GL_MAX_DEBUG_GROUP_STACK_DEPTH:
        return "GL_MAX_DEBUG_GROUP_STACK_DEPTH";
    case GL_DEBUG_GROUP_STACK_DEPTH:
        return "GL_DEBUG_GROUP_STACK_DEPTH";
    case GL_MAX_UNIFORM_LOCATIONS:
        return "GL_MAX_UNIFORM_LOCATIONS";
    case GL_INTERNALFORMAT_SUPPORTED:
        return "GL_INTERNALFORMAT_SUPPORTED";
    case GL_INTERNALFORMAT_PREFERRED:
        return "GL_INTERNALFORMAT_PREFERRED";
    case GL_INTERNALFORMAT_RED_SIZE:
        return "GL_INTERNALFORMAT_RED_SIZE";
    case GL_INTERNALFORMAT_GREEN_SIZE:
        return "GL_INTERNALFORMAT_GREEN_SIZE";
    case GL_INTERNALFORMAT_BLUE_SIZE:
        return "GL_INTERNALFORMAT_BLUE_SIZE";
    case GL_INTERNALFORMAT_ALPHA_SIZE:
        return "GL_INTERNALFORMAT_ALPHA_SIZE";
    case GL_INTERNALFORMAT_DEPTH_SIZE:
        return "GL_INTERNALFORMAT_DEPTH_SIZE";
    case GL_INTERNALFORMAT_STENCIL_SIZE:
        return "GL_INTERNALFORMAT_STENCIL_SIZE";
    case GL_INTERNALFORMAT_SHARED_SIZE:
        return "GL_INTERNALFORMAT_SHARED_SIZE";
    case GL_INTERNALFORMAT_RED_TYPE:
        return "GL_INTERNALFORMAT_RED_TYPE";
    case GL_INTERNALFORMAT_GREEN_TYPE:
        return "GL_INTERNALFORMAT_GREEN_TYPE";
    case GL_INTERNALFORMAT_BLUE_TYPE:
        return "GL_INTERNALFORMAT_BLUE_TYPE";
    case GL_INTERNALFORMAT_ALPHA_TYPE:
        return "GL_INTERNALFORMAT_ALPHA_TYPE";
    case GL_INTERNALFORMAT_DEPTH_TYPE:
        return "GL_INTERNALFORMAT_DEPTH_TYPE";
    case GL_INTERNALFORMAT_STENCIL_TYPE:
        return "GL_INTERNALFORMAT_STENCIL_TYPE";
    case GL_MAX_WIDTH:
        return "GL_MAX_WIDTH";
    case GL_MAX_HEIGHT:
        return "GL_MAX_HEIGHT";
    case GL_MAX_DEPTH:
        return "GL_MAX_DEPTH";
    case GL_MAX_LAYERS:
        return "GL_MAX_LAYERS";
    case GL_MAX_COMBINED_DIMENSIONS:
        return "GL_MAX_COMBINED_DIMENSIONS";
    case GL_COLOR_COMPONENTS:
        return "GL_COLOR_COMPONENTS";
    case GL_DEPTH_COMPONENTS:
        return "GL_DEPTH_COMPONENTS";
    case GL_STENCIL_COMPONENTS:
        return "GL_STENCIL_COMPONENTS";
    case GL_COLOR_RENDERABLE:
        return "GL_COLOR_RENDERABLE";
    case GL_DEPTH_RENDERABLE:
        return "GL_DEPTH_RENDERABLE";
    case GL_STENCIL_RENDERABLE:
        return "GL_STENCIL_RENDERABLE";
    case GL_FRAMEBUFFER_RENDERABLE:
        return "GL_FRAMEBUFFER_RENDERABLE";
    case GL_FRAMEBUFFER_RENDERABLE_LAYERED:
        return "GL_FRAMEBUFFER_RENDERABLE_LAYERED";
    case GL_FRAMEBUFFER_BLEND:
        return "GL_FRAMEBUFFER_BLEND";
    case GL_READ_PIXELS:
        return "GL_READ_PIXELS";
    case GL_READ_PIXELS_FORMAT:
        return "GL_READ_PIXELS_FORMAT";
    case GL_READ_PIXELS_TYPE:
        return "GL_READ_PIXELS_TYPE";
    case GL_TEXTURE_IMAGE_FORMAT:
        return "GL_TEXTURE_IMAGE_FORMAT";
    case GL_TEXTURE_IMAGE_TYPE:
        return "GL_TEXTURE_IMAGE_TYPE";
    case GL_GET_TEXTURE_IMAGE_FORMAT:
        return "GL_GET_TEXTURE_IMAGE_FORMAT";
    case GL_GET_TEXTURE_IMAGE_TYPE:
        return "GL_GET_TEXTURE_IMAGE_TYPE";
    case GL_MIPMAP:
        return "GL_MIPMAP";
    case GL_MANUAL_GENERATE_MIPMAP:
        return "GL_MANUAL_GENERATE_MIPMAP";
    case GL_AUTO_GENERATE_MIPMAP:
        return "GL_AUTO_GENERATE_MIPMAP";
    case GL_COLOR_ENCODING:
        return "GL_COLOR_ENCODING";
    case GL_SRGB_READ:
        return "GL_SRGB_READ";
    case GL_SRGB_WRITE:
        return "GL_SRGB_WRITE";
    case GL_SRGB_DECODE_ARB:
        return "GL_SRGB_DECODE_ARB";
    case GL_FILTER:
        return "GL_FILTER";
    case GL_VERTEX_TEXTURE:
        return "GL_VERTEX_TEXTURE";
    case GL_TESS_CONTROL_TEXTURE:
        return "GL_TESS_CONTROL_TEXTURE";
    case GL_TESS_EVALUATION_TEXTURE:
        return "GL_TESS_EVALUATION_TEXTURE";
    case GL_GEOMETRY_TEXTURE:
        return "GL_GEOMETRY_TEXTURE";
    case GL_FRAGMENT_TEXTURE:
        return "GL_FRAGMENT_TEXTURE";
    case GL_COMPUTE_TEXTURE:
        return "GL_COMPUTE_TEXTURE";
    case GL_TEXTURE_SHADOW:
        return "GL_TEXTURE_SHADOW";
    case GL_TEXTURE_GATHER:
        return "GL_TEXTURE_GATHER";
    case GL_TEXTURE_GATHER_SHADOW:
        return "GL_TEXTURE_GATHER_SHADOW";
    case GL_SHADER_IMAGE_LOAD:
        return "GL_SHADER_IMAGE_LOAD";
    case GL_SHADER_IMAGE_STORE:
        return "GL_SHADER_IMAGE_STORE";
    case GL_SHADER_IMAGE_ATOMIC:
        return "GL_SHADER_IMAGE_ATOMIC";
    case GL_IMAGE_TEXEL_SIZE:
        return "GL_IMAGE_TEXEL_SIZE";
    case GL_IMAGE_COMPATIBILITY_CLASS:
        return "GL_IMAGE_COMPATIBILITY_CLASS";
    case GL_IMAGE_PIXEL_FORMAT:
        return "GL_IMAGE_PIXEL_FORMAT";
    case GL_IMAGE_PIXEL_TYPE:
        return "GL_IMAGE_PIXEL_TYPE";
    case GL_SIMULTANEOUS_TEXTURE_AND_DEPTH_TEST:
        return "GL_SIMULTANEOUS_TEXTURE_AND_DEPTH_TEST";
    case GL_SIMULTANEOUS_TEXTURE_AND_STENCIL_TEST:
        return "GL_SIMULTANEOUS_TEXTURE_AND_STENCIL_TEST";
    case GL_SIMULTANEOUS_TEXTURE_AND_DEPTH_WRITE:
        return "GL_SIMULTANEOUS_TEXTURE_AND_DEPTH_WRITE";
    case GL_SIMULTANEOUS_TEXTURE_AND_STENCIL_WRITE:
        return "GL_SIMULTANEOUS_TEXTURE_AND_STENCIL_WRITE";
    case GL_TEXTURE_COMPRESSED_BLOCK_WIDTH:
        return "GL_TEXTURE_COMPRESSED_BLOCK_WIDTH";
    case GL_TEXTURE_COMPRESSED_BLOCK_HEIGHT:
        return "GL_TEXTURE_COMPRESSED_BLOCK_HEIGHT";
    case GL_TEXTURE_COMPRESSED_BLOCK_SIZE:
        return "GL_TEXTURE_COMPRESSED_BLOCK_SIZE";
    case GL_CLEAR_BUFFER:
        return "GL_CLEAR_BUFFER";
    case GL_TEXTURE_VIEW:
        return "GL_TEXTURE_VIEW";
    case GL_VIEW_COMPATIBILITY_CLASS:
        return "GL_VIEW_COMPATIBILITY_CLASS";
    case GL_FULL_SUPPORT:
        return "GL_FULL_SUPPORT";
    case GL_CAVEAT_SUPPORT:
        return "GL_CAVEAT_SUPPORT";
    case GL_IMAGE_CLASS_4_X_32:
        return "GL_IMAGE_CLASS_4_X_32";
    case GL_IMAGE_CLASS_2_X_32:
        return "GL_IMAGE_CLASS_2_X_32";
    case GL_IMAGE_CLASS_1_X_32:
        return "GL_IMAGE_CLASS_1_X_32";
    case GL_IMAGE_CLASS_4_X_16:
        return "GL_IMAGE_CLASS_4_X_16";
    case GL_IMAGE_CLASS_2_X_16:
        return "GL_IMAGE_CLASS_2_X_16";
    case GL_IMAGE_CLASS_1_X_16:
        return "GL_IMAGE_CLASS_1_X_16";
    case GL_IMAGE_CLASS_4_X_8:
        return "GL_IMAGE_CLASS_4_X_8";
    case GL_IMAGE_CLASS_2_X_8:
        return "GL_IMAGE_CLASS_2_X_8";
    case GL_IMAGE_CLASS_1_X_8:
        return "GL_IMAGE_CLASS_1_X_8";
    case GL_IMAGE_CLASS_11_11_10:
        return "GL_IMAGE_CLASS_11_11_10";
    case GL_IMAGE_CLASS_10_10_10_2:
        return "GL_IMAGE_CLASS_10_10_10_2";
    case GL_VIEW_CLASS_128_BITS:
        return "GL_VIEW_CLASS_128_BITS";
    case GL_VIEW_CLASS_96_BITS:
        return "GL_VIEW_CLASS_96_BITS";
    case GL_VIEW_CLASS_64_BITS:
        return "GL_VIEW_CLASS_64_BITS";
    case GL_VIEW_CLASS_48_BITS:
        return "GL_VIEW_CLASS_48_BITS";
    case GL_VIEW_CLASS_32_BITS:
        return "GL_VIEW_CLASS_32_BITS";
    case GL_VIEW_CLASS_24_BITS:
        return "GL_VIEW_CLASS_24_BITS";
    case GL_VIEW_CLASS_16_BITS:
        return "GL_VIEW_CLASS_16_BITS";
    case GL_VIEW_CLASS_8_BITS:
        return "GL_VIEW_CLASS_8_BITS";
    case GL_VIEW_CLASS_S3TC_DXT1_RGB:
        return "GL_VIEW_CLASS_S3TC_DXT1_RGB";
    case GL_VIEW_CLASS_S3TC_DXT1_RGBA:
        return "GL_VIEW_CLASS_S3TC_DXT1_RGBA";
    case GL_VIEW_CLASS_S3TC_DXT3_RGBA:
        return "GL_VIEW_CLASS_S3TC_DXT3_RGBA";
    case GL_VIEW_CLASS_S3TC_DXT5_RGBA:
        return "GL_VIEW_CLASS_S3TC_DXT5_RGBA";
    case GL_VIEW_CLASS_RGTC1_RED:
        return "GL_VIEW_CLASS_RGTC1_RED";
    case GL_VIEW_CLASS_RGTC2_RG:
        return "GL_VIEW_CLASS_RGTC2_RG";
    case GL_VIEW_CLASS_BPTC_UNORM:
        return "GL_VIEW_CLASS_BPTC_UNORM";
    case GL_VIEW_CLASS_BPTC_FLOAT:
        return "GL_VIEW_CLASS_BPTC_FLOAT";
    case GL_VERTEX_ATTRIB_BINDING:
        return "GL_VERTEX_ATTRIB_BINDING";
    case GL_VERTEX_ATTRIB_RELATIVE_OFFSET:
        return "GL_VERTEX_ATTRIB_RELATIVE_OFFSET";
    case GL_VERTEX_BINDING_DIVISOR:
        return "GL_VERTEX_BINDING_DIVISOR";
    case GL_VERTEX_BINDING_OFFSET:
        return "GL_VERTEX_BINDING_OFFSET";
    case GL_VERTEX_BINDING_STRIDE:
        return "GL_VERTEX_BINDING_STRIDE";
    case GL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET:
        return "GL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET";
    case GL_MAX_VERTEX_ATTRIB_BINDINGS:
        return "GL_MAX_VERTEX_ATTRIB_BINDINGS";
    case GL_TEXTURE_VIEW_MIN_LEVEL:
        return "GL_TEXTURE_VIEW_MIN_LEVEL";
    case GL_TEXTURE_VIEW_NUM_LEVELS:
        return "GL_TEXTURE_VIEW_NUM_LEVELS";
    case GL_TEXTURE_VIEW_MIN_LAYER:
        return "GL_TEXTURE_VIEW_MIN_LAYER";
    case GL_TEXTURE_VIEW_NUM_LAYERS:
        return "GL_TEXTURE_VIEW_NUM_LAYERS";
#endif
    case GL_TEXTURE_IMMUTABLE_LEVELS:
        return "GL_TEXTURE_IMMUTABLE_LEVELS";
#ifndef GL_ES_VERSION_3_0
    case GL_BUFFER:
        return "GL_BUFFER";
    case GL_SHADER:
        return "GL_SHADER";
    case GL_PROGRAM:
        return "GL_PROGRAM";
    case GL_QUERY:
        return "GL_QUERY";
    case GL_PROGRAM_PIPELINE:
        return "GL_PROGRAM_PIPELINE";
    case GL_MAX_VERTEX_ATTRIB_STRIDE:
        return "GL_MAX_VERTEX_ATTRIB_STRIDE";
#endif
    case GL_SAMPLER:
        return "GL_SAMPLER";
#ifndef GL_ES_VERSION_3_0
    case GL_DISPLAY_LIST:
        return "GL_DISPLAY_LIST";
    case GL_MAX_LABEL_LENGTH:
        return "GL_MAX_LABEL_LENGTH";
    case GL_NUM_SHADING_LANGUAGE_VERSIONS:
        return "GL_NUM_SHADING_LANGUAGE_VERSIONS";
    case GL_QUERY_TARGET:
        return "GL_QUERY_TARGET";
    case GL_TRANSFORM_FEEDBACK_OVERFLOW_ARB:
        return "GL_TRANSFORM_FEEDBACK_OVERFLOW_ARB";
    case GL_TRANSFORM_FEEDBACK_STREAM_OVERFLOW_ARB:
        return "GL_TRANSFORM_FEEDBACK_STREAM_OVERFLOW_ARB";
    case GL_VERTICES_SUBMITTED_ARB:
        return "GL_VERTICES_SUBMITTED_ARB";
    case GL_PRIMITIVES_SUBMITTED_ARB:
        return "GL_PRIMITIVES_SUBMITTED_ARB";
    case GL_VERTEX_SHADER_INVOCATIONS_ARB:
        return "GL_VERTEX_SHADER_INVOCATIONS_ARB";
    case GL_TESS_CONTROL_SHADER_PATCHES_ARB:
        return "GL_TESS_CONTROL_SHADER_PATCHES_ARB";
    case GL_TESS_EVALUATION_SHADER_INVOCATIONS_ARB:
        return "GL_TESS_EVALUATION_SHADER_INVOCATIONS_ARB";
    case GL_GEOMETRY_SHADER_PRIMITIVES_EMITTED_ARB:
        return "GL_GEOMETRY_SHADER_PRIMITIVES_EMITTED_ARB";
    case GL_FRAGMENT_SHADER_INVOCATIONS_ARB:
        return "GL_FRAGMENT_SHADER_INVOCATIONS_ARB";
    case GL_COMPUTE_SHADER_INVOCATIONS_ARB:
        return "GL_COMPUTE_SHADER_INVOCATIONS_ARB";
    case GL_CLIPPING_INPUT_PRIMITIVES_ARB:
        return "GL_CLIPPING_INPUT_PRIMITIVES_ARB";
    case GL_CLIPPING_OUTPUT_PRIMITIVES_ARB:
        return "GL_CLIPPING_OUTPUT_PRIMITIVES_ARB";
    case GL_SPARSE_BUFFER_PAGE_SIZE_ARB:
        return "GL_SPARSE_BUFFER_PAGE_SIZE_ARB";
    case GL_MAX_CULL_DISTANCES:
        return "GL_MAX_CULL_DISTANCES";
    case GL_MAX_COMBINED_CLIP_AND_CULL_DISTANCES:
        return "GL_MAX_COMBINED_CLIP_AND_CULL_DISTANCES";
    case GL_CONTEXT_RELEASE_BEHAVIOR:
        return "GL_CONTEXT_RELEASE_BEHAVIOR";
    case GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH:
        return "GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH";
    case GL_DEPTH_PASS_INSTRUMENT_SGIX:
        return "GL_DEPTH_PASS_INSTRUMENT_SGIX";
    case GL_DEPTH_PASS_INSTRUMENT_COUNTERS_SGIX:
        return "GL_DEPTH_PASS_INSTRUMENT_COUNTERS_SGIX";
    case GL_DEPTH_PASS_INSTRUMENT_MAX_SGIX:
        return "GL_DEPTH_PASS_INSTRUMENT_MAX_SGIX";
    case GL_CONVOLUTION_HINT_SGIX:
        return "GL_CONVOLUTION_HINT_SGIX";
    case GL_YCRCB_SGIX:
        return "GL_YCRCB_SGIX";
    case GL_YCRCBA_SGIX:
        return "GL_YCRCBA_SGIX";
    case GL_ALPHA_MIN_SGIX:
        return "GL_ALPHA_MIN_SGIX";
    case GL_ALPHA_MAX_SGIX:
        return "GL_ALPHA_MAX_SGIX";
    case GL_SCALEBIAS_HINT_SGIX:
        return "GL_SCALEBIAS_HINT_SGIX";
    case GL_ASYNC_MARKER_SGIX:
        return "GL_ASYNC_MARKER_SGIX";
    case GL_PIXEL_TEX_GEN_MODE_SGIX:
        return "GL_PIXEL_TEX_GEN_MODE_SGIX";
    case GL_ASYNC_HISTOGRAM_SGIX:
        return "GL_ASYNC_HISTOGRAM_SGIX";
    case GL_MAX_ASYNC_HISTOGRAM_SGIX:
        return "GL_MAX_ASYNC_HISTOGRAM_SGIX";
    case GL_PIXEL_TRANSFORM_2D_EXT:
        return "GL_PIXEL_TRANSFORM_2D_EXT";
    case GL_PIXEL_MAG_FILTER_EXT:
        return "GL_PIXEL_MAG_FILTER_EXT";
    case GL_PIXEL_MIN_FILTER_EXT:
        return "GL_PIXEL_MIN_FILTER_EXT";
    case GL_PIXEL_CUBIC_WEIGHT_EXT:
        return "GL_PIXEL_CUBIC_WEIGHT_EXT";
    case GL_CUBIC_EXT:
        return "GL_CUBIC_EXT";
    case GL_AVERAGE_EXT:
        return "GL_AVERAGE_EXT";
    case GL_PIXEL_TRANSFORM_2D_STACK_DEPTH_EXT:
        return "GL_PIXEL_TRANSFORM_2D_STACK_DEPTH_EXT";
    case GL_MAX_PIXEL_TRANSFORM_2D_STACK_DEPTH_EXT:
        return "GL_MAX_PIXEL_TRANSFORM_2D_STACK_DEPTH_EXT";
    case GL_PIXEL_TRANSFORM_2D_MATRIX_EXT:
        return "GL_PIXEL_TRANSFORM_2D_MATRIX_EXT";
    case GL_FRAGMENT_MATERIAL_EXT:
        return "GL_FRAGMENT_MATERIAL_EXT";
    case GL_FRAGMENT_NORMAL_EXT:
        return "GL_FRAGMENT_NORMAL_EXT";
    case GL_FRAGMENT_COLOR_EXT:
        return "GL_FRAGMENT_COLOR_EXT";
    case GL_ATTENUATION_EXT:
        return "GL_ATTENUATION_EXT";
    case GL_SHADOW_ATTENUATION_EXT:
        return "GL_SHADOW_ATTENUATION_EXT";
    case GL_TEXTURE_APPLICATION_MODE_EXT:
        return "GL_TEXTURE_APPLICATION_MODE_EXT";
    case GL_TEXTURE_LIGHT_EXT:
        return "GL_TEXTURE_LIGHT_EXT";
    case GL_TEXTURE_MATERIAL_FACE_EXT:
        return "GL_TEXTURE_MATERIAL_FACE_EXT";
    case GL_TEXTURE_MATERIAL_PARAMETER_EXT:
        return "GL_TEXTURE_MATERIAL_PARAMETER_EXT";
    case GL_PIXEL_TEXTURE_SGIS:
        return "GL_PIXEL_TEXTURE_SGIS";
    case GL_PIXEL_FRAGMENT_RGB_SOURCE_SGIS:
        return "GL_PIXEL_FRAGMENT_RGB_SOURCE_SGIS";
    case GL_PIXEL_FRAGMENT_ALPHA_SOURCE_SGIS:
        return "GL_PIXEL_FRAGMENT_ALPHA_SOURCE_SGIS";
    case GL_PIXEL_GROUP_COLOR_SGIS:
        return "GL_PIXEL_GROUP_COLOR_SGIS";
    case GL_ASYNC_TEX_IMAGE_SGIX:
        return "GL_ASYNC_TEX_IMAGE_SGIX";
    case GL_ASYNC_DRAW_PIXELS_SGIX:
        return "GL_ASYNC_DRAW_PIXELS_SGIX";
    case GL_ASYNC_READ_PIXELS_SGIX:
        return "GL_ASYNC_READ_PIXELS_SGIX";
    case GL_MAX_ASYNC_TEX_IMAGE_SGIX:
        return "GL_MAX_ASYNC_TEX_IMAGE_SGIX";
    case GL_MAX_ASYNC_DRAW_PIXELS_SGIX:
        return "GL_MAX_ASYNC_DRAW_PIXELS_SGIX";
    case GL_MAX_ASYNC_READ_PIXELS_SGIX:
        return "GL_MAX_ASYNC_READ_PIXELS_SGIX";
    case GL_UNSIGNED_BYTE_2_3_3_REV:
        return "GL_UNSIGNED_BYTE_2_3_3_REV";
#endif
    case GL_UNSIGNED_SHORT_5_6_5:
        return "GL_UNSIGNED_SHORT_5_6_5";
#ifndef GL_ES_VERSION_3_0
    case GL_UNSIGNED_SHORT_5_6_5_REV:
        return "GL_UNSIGNED_SHORT_5_6_5_REV";
    case GL_UNSIGNED_SHORT_4_4_4_4_REV:
        return "GL_UNSIGNED_SHORT_4_4_4_4_REV";
    case GL_UNSIGNED_SHORT_1_5_5_5_REV:
        return "GL_UNSIGNED_SHORT_1_5_5_5_REV";
    case GL_UNSIGNED_INT_8_8_8_8_REV:
        return "GL_UNSIGNED_INT_8_8_8_8_REV";
#endif
    case GL_UNSIGNED_INT_2_10_10_10_REV:
        return "GL_UNSIGNED_INT_2_10_10_10_REV";
#ifndef GL_ES_VERSION_3_0
    case GL_TEXTURE_MAX_CLAMP_S_SGIX:
        return "GL_TEXTURE_MAX_CLAMP_S_SGIX";
    case GL_TEXTURE_MAX_CLAMP_T_SGIX:
        return "GL_TEXTURE_MAX_CLAMP_T_SGIX";
    case GL_TEXTURE_MAX_CLAMP_R_SGIX:
        return "GL_TEXTURE_MAX_CLAMP_R_SGIX";
#endif
    case GL_MIRRORED_REPEAT:
        return "GL_MIRRORED_REPEAT";
#ifndef GL_ES_VERSION_3_0
    case GL_RGB_S3TC:
        return "GL_RGB_S3TC";
    case GL_RGB4_S3TC:
        return "GL_RGB4_S3TC";
    case GL_RGBA_S3TC:
        return "GL_RGBA_S3TC";
    case GL_RGBA4_S3TC:
        return "GL_RGBA4_S3TC";
    case GL_RGBA_DXT5_S3TC:
        return "GL_RGBA_DXT5_S3TC";
    case GL_RGBA4_DXT5_S3TC:
        return "GL_RGBA4_DXT5_S3TC";
    case GL_VERTEX_PRECLIP_SGIX:
        return "GL_VERTEX_PRECLIP_SGIX";
    case GL_VERTEX_PRECLIP_HINT_SGIX:
        return "GL_VERTEX_PRECLIP_HINT_SGIX";
#endif
    case GL_COMPRESSED_RGB_S3TC_DXT1_EXT:
        return "GL_COMPRESSED_RGB_S3TC_DXT1_EXT";
    case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT:
        return "GL_COMPRESSED_RGBA_S3TC_DXT1_EXT";
    case GL_COMPRESSED_RGBA_S3TC_DXT3_EXT:
        return "GL_COMPRESSED_RGBA_S3TC_DXT3_EXT";
    case GL_COMPRESSED_RGBA_S3TC_DXT5_EXT:
        return "GL_COMPRESSED_RGBA_S3TC_DXT5_EXT";
#ifndef GL_ES_VERSION_3_0
    case GL_PARALLEL_ARRAYS_INTEL:
        return "GL_PARALLEL_ARRAYS_INTEL";
    case GL_VERTEX_ARRAY_PARALLEL_POINTERS_INTEL:
        return "GL_VERTEX_ARRAY_PARALLEL_POINTERS_INTEL";
    case GL_NORMAL_ARRAY_PARALLEL_POINTERS_INTEL:
        return "GL_NORMAL_ARRAY_PARALLEL_POINTERS_INTEL";
    case GL_COLOR_ARRAY_PARALLEL_POINTERS_INTEL:
        return "GL_COLOR_ARRAY_PARALLEL_POINTERS_INTEL";
    case GL_TEXTURE_COORD_ARRAY_PARALLEL_POINTERS_INTEL:
        return "GL_TEXTURE_COORD_ARRAY_PARALLEL_POINTERS_INTEL";
#endif
    case GL_PERFQUERY_DONOT_FLUSH_INTEL:
        return "GL_PERFQUERY_DONOT_FLUSH_INTEL";
    case GL_PERFQUERY_FLUSH_INTEL:
        return "GL_PERFQUERY_FLUSH_INTEL";
    case GL_PERFQUERY_WAIT_INTEL:
        return "GL_PERFQUERY_WAIT_INTEL";
#ifndef GL_ES_VERSION_3_0
    case GL_TEXTURE_MEMORY_LAYOUT_INTEL:
        return "GL_TEXTURE_MEMORY_LAYOUT_INTEL";
    case GL_FRAGMENT_LIGHTING_SGIX:
        return "GL_FRAGMENT_LIGHTING_SGIX";
    case GL_FRAGMENT_COLOR_MATERIAL_SGIX:
        return "GL_FRAGMENT_COLOR_MATERIAL_SGIX";
    case GL_FRAGMENT_COLOR_MATERIAL_FACE_SGIX:
        return "GL_FRAGMENT_COLOR_MATERIAL_FACE_SGIX";
    case GL_FRAGMENT_COLOR_MATERIAL_PARAMETER_SGIX:
        return "GL_FRAGMENT_COLOR_MATERIAL_PARAMETER_SGIX";
    case GL_MAX_FRAGMENT_LIGHTS_SGIX:
        return "GL_MAX_FRAGMENT_LIGHTS_SGIX";
    case GL_MAX_ACTIVE_LIGHTS_SGIX:
        return "GL_MAX_ACTIVE_LIGHTS_SGIX";
    case GL_CURRENT_RASTER_NORMAL_SGIX:
        return "GL_CURRENT_RASTER_NORMAL_SGIX";
    case GL_LIGHT_ENV_MODE_SGIX:
        return "GL_LIGHT_ENV_MODE_SGIX";
    case GL_FRAGMENT_LIGHT_MODEL_LOCAL_VIEWER_SGIX:
        return "GL_FRAGMENT_LIGHT_MODEL_LOCAL_VIEWER_SGIX";
    case GL_FRAGMENT_LIGHT_MODEL_TWO_SIDE_SGIX:
        return "GL_FRAGMENT_LIGHT_MODEL_TWO_SIDE_SGIX";
    case GL_FRAGMENT_LIGHT_MODEL_AMBIENT_SGIX:
        return "GL_FRAGMENT_LIGHT_MODEL_AMBIENT_SGIX";
    case GL_FRAGMENT_LIGHT_MODEL_NORMAL_INTERPOLATION_SGIX:
        return "GL_FRAGMENT_LIGHT_MODEL_NORMAL_INTERPOLATION_SGIX";
    case GL_FRAGMENT_LIGHT0_SGIX:
        return "GL_FRAGMENT_LIGHT0_SGIX";
    case GL_FRAGMENT_LIGHT1_SGIX:
        return "GL_FRAGMENT_LIGHT1_SGIX";
    case GL_FRAGMENT_LIGHT2_SGIX:
        return "GL_FRAGMENT_LIGHT2_SGIX";
    case GL_FRAGMENT_LIGHT3_SGIX:
        return "GL_FRAGMENT_LIGHT3_SGIX";
    case GL_FRAGMENT_LIGHT4_SGIX:
        return "GL_FRAGMENT_LIGHT4_SGIX";
    case GL_FRAGMENT_LIGHT5_SGIX:
        return "GL_FRAGMENT_LIGHT5_SGIX";
    case GL_FRAGMENT_LIGHT6_SGIX:
        return "GL_FRAGMENT_LIGHT6_SGIX";
    case GL_FRAGMENT_LIGHT7_SGIX:
        return "GL_FRAGMENT_LIGHT7_SGIX";
    case GL_PACK_RESAMPLE_SGIX:
        return "GL_PACK_RESAMPLE_SGIX";
    case GL_UNPACK_RESAMPLE_SGIX:
        return "GL_UNPACK_RESAMPLE_SGIX";
    case GL_RESAMPLE_DECIMATE_SGIX:
        return "GL_RESAMPLE_DECIMATE_SGIX";
    case GL_RESAMPLE_REPLICATE_SGIX:
        return "GL_RESAMPLE_REPLICATE_SGIX";
    case GL_RESAMPLE_ZERO_FILL_SGIX:
        return "GL_RESAMPLE_ZERO_FILL_SGIX";
    case GL_TANGENT_ARRAY_EXT:
        return "GL_TANGENT_ARRAY_EXT";
    case GL_BINORMAL_ARRAY_EXT:
        return "GL_BINORMAL_ARRAY_EXT";
    case GL_CURRENT_TANGENT_EXT:
        return "GL_CURRENT_TANGENT_EXT";
    case GL_CURRENT_BINORMAL_EXT:
        return "GL_CURRENT_BINORMAL_EXT";
    case GL_TANGENT_ARRAY_TYPE_EXT:
        return "GL_TANGENT_ARRAY_TYPE_EXT";
    case GL_TANGENT_ARRAY_STRIDE_EXT:
        return "GL_TANGENT_ARRAY_STRIDE_EXT";
    case GL_BINORMAL_ARRAY_TYPE_EXT:
        return "GL_BINORMAL_ARRAY_TYPE_EXT";
    case GL_BINORMAL_ARRAY_STRIDE_EXT:
        return "GL_BINORMAL_ARRAY_STRIDE_EXT";
    case GL_TANGENT_ARRAY_POINTER_EXT:
        return "GL_TANGENT_ARRAY_POINTER_EXT";
    case GL_BINORMAL_ARRAY_POINTER_EXT:
        return "GL_BINORMAL_ARRAY_POINTER_EXT";
    case GL_MAP1_TANGENT_EXT:
        return "GL_MAP1_TANGENT_EXT";
    case GL_MAP2_TANGENT_EXT:
        return "GL_MAP2_TANGENT_EXT";
    case GL_MAP1_BINORMAL_EXT:
        return "GL_MAP1_BINORMAL_EXT";
    case GL_MAP2_BINORMAL_EXT:
        return "GL_MAP2_BINORMAL_EXT";
    case GL_NEAREST_CLIPMAP_NEAREST_SGIX:
        return "GL_NEAREST_CLIPMAP_NEAREST_SGIX";
    case GL_NEAREST_CLIPMAP_LINEAR_SGIX:
        return "GL_NEAREST_CLIPMAP_LINEAR_SGIX";
    case GL_LINEAR_CLIPMAP_NEAREST_SGIX:
        return "GL_LINEAR_CLIPMAP_NEAREST_SGIX";
    case GL_FOG_COORD_SRC:
        return "GL_FOG_COORD_SRC";
    case GL_FOG_COORD:
        return "GL_FOG_COORD";
    case GL_FRAGMENT_DEPTH:
        return "GL_FRAGMENT_DEPTH";
    case GL_CURRENT_FOG_COORD:
        return "GL_CURRENT_FOG_COORD";
    case GL_FOG_COORD_ARRAY_TYPE:
        return "GL_FOG_COORD_ARRAY_TYPE";
    case GL_FOG_COORD_ARRAY_STRIDE:
        return "GL_FOG_COORD_ARRAY_STRIDE";
    case GL_FOG_COORD_ARRAY_POINTER:
        return "GL_FOG_COORD_ARRAY_POINTER";
    case GL_FOG_COORD_ARRAY:
        return "GL_FOG_COORD_ARRAY";
    case GL_COLOR_SUM:
        return "GL_COLOR_SUM";
    case GL_CURRENT_SECONDARY_COLOR:
        return "GL_CURRENT_SECONDARY_COLOR";
    case GL_SECONDARY_COLOR_ARRAY_SIZE:
        return "GL_SECONDARY_COLOR_ARRAY_SIZE";
    case GL_SECONDARY_COLOR_ARRAY_TYPE:
        return "GL_SECONDARY_COLOR_ARRAY_TYPE";
    case GL_SECONDARY_COLOR_ARRAY_STRIDE:
        return "GL_SECONDARY_COLOR_ARRAY_STRIDE";
    case GL_SECONDARY_COLOR_ARRAY_POINTER:
        return "GL_SECONDARY_COLOR_ARRAY_POINTER";
    case GL_SECONDARY_COLOR_ARRAY:
        return "GL_SECONDARY_COLOR_ARRAY";
    case GL_CURRENT_RASTER_SECONDARY_COLOR:
        return "GL_CURRENT_RASTER_SECONDARY_COLOR";
#endif
    case GL_ALIASED_POINT_SIZE_RANGE:
        return "GL_ALIASED_POINT_SIZE_RANGE";
    case GL_ALIASED_LINE_WIDTH_RANGE:
        return "GL_ALIASED_LINE_WIDTH_RANGE";
#ifndef GL_ES_VERSION_3_0
    case GL_SCREEN_COORDINATES_REND:
        return "GL_SCREEN_COORDINATES_REND";
    case GL_INVERTED_SCREEN_W_REND:
        return "GL_INVERTED_SCREEN_W_REND";
#endif
    case GL_TEXTURE0:
        return "GL_TEXTURE0";
    case GL_TEXTURE1:
        return "GL_TEXTURE1";
    case GL_TEXTURE2:
        return "GL_TEXTURE2";
    case GL_TEXTURE3:
        return "GL_TEXTURE3";
    case GL_TEXTURE4:
        return "GL_TEXTURE4";
    case GL_TEXTURE5:
        return "GL_TEXTURE5";
    case GL_TEXTURE6:
        return "GL_TEXTURE6";
    case GL_TEXTURE7:
        return "GL_TEXTURE7";
    case GL_TEXTURE8:
        return "GL_TEXTURE8";
    case GL_TEXTURE9:
        return "GL_TEXTURE9";
    case GL_TEXTURE10:
        return "GL_TEXTURE10";
    case GL_TEXTURE11:
        return "GL_TEXTURE11";
    case GL_TEXTURE12:
        return "GL_TEXTURE12";
    case GL_TEXTURE13:
        return "GL_TEXTURE13";
    case GL_TEXTURE14:
        return "GL_TEXTURE14";
    case GL_TEXTURE15:
        return "GL_TEXTURE15";
    case GL_TEXTURE16:
        return "GL_TEXTURE16";
    case GL_TEXTURE17:
        return "GL_TEXTURE17";
    case GL_TEXTURE18:
        return "GL_TEXTURE18";
    case GL_TEXTURE19:
        return "GL_TEXTURE19";
    case GL_TEXTURE20:
        return "GL_TEXTURE20";
    case GL_TEXTURE21:
        return "GL_TEXTURE21";
    case GL_TEXTURE22:
        return "GL_TEXTURE22";
    case GL_TEXTURE23:
        return "GL_TEXTURE23";
    case GL_TEXTURE24:
        return "GL_TEXTURE24";
    case GL_TEXTURE25:
        return "GL_TEXTURE25";
    case GL_TEXTURE26:
        return "GL_TEXTURE26";
    case GL_TEXTURE27:
        return "GL_TEXTURE27";
    case GL_TEXTURE28:
        return "GL_TEXTURE28";
    case GL_TEXTURE29:
        return "GL_TEXTURE29";
    case GL_TEXTURE30:
        return "GL_TEXTURE30";
    case GL_TEXTURE31:
        return "GL_TEXTURE31";
    case GL_ACTIVE_TEXTURE:
        return "GL_ACTIVE_TEXTURE";
#ifndef GL_ES_VERSION_3_0
    case GL_CLIENT_ACTIVE_TEXTURE:
        return "GL_CLIENT_ACTIVE_TEXTURE";
    case GL_MAX_TEXTURE_UNITS:
        return "GL_MAX_TEXTURE_UNITS";
    case GL_TRANSPOSE_MODELVIEW_MATRIX:
        return "GL_TRANSPOSE_MODELVIEW_MATRIX";
    case GL_TRANSPOSE_PROJECTION_MATRIX:
        return "GL_TRANSPOSE_PROJECTION_MATRIX";
    case GL_TRANSPOSE_TEXTURE_MATRIX:
        return "GL_TRANSPOSE_TEXTURE_MATRIX";
    case GL_TRANSPOSE_COLOR_MATRIX:
        return "GL_TRANSPOSE_COLOR_MATRIX";
    case GL_SUBTRACT:
        return "GL_SUBTRACT";
#endif
    case GL_MAX_RENDERBUFFER_SIZE:
        return "GL_MAX_RENDERBUFFER_SIZE";
#ifndef GL_ES_VERSION_3_0
    case GL_COMPRESSED_ALPHA:
        return "GL_COMPRESSED_ALPHA";
    case GL_COMPRESSED_LUMINANCE:
        return "GL_COMPRESSED_LUMINANCE";
    case GL_COMPRESSED_LUMINANCE_ALPHA:
        return "GL_COMPRESSED_LUMINANCE_ALPHA";
    case GL_COMPRESSED_INTENSITY:
        return "GL_COMPRESSED_INTENSITY";
    case GL_COMPRESSED_RGB:
        return "GL_COMPRESSED_RGB";
    case GL_COMPRESSED_RGBA:
        return "GL_COMPRESSED_RGBA";
    case GL_TEXTURE_COMPRESSION_HINT:
        return "GL_TEXTURE_COMPRESSION_HINT";
    case GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_CONTROL_SHADER:
        return "GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_CONTROL_SHADER";
    case GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_EVALUATION_SHADER:
        return "GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_EVALUATION_SHADER";
#endif
    case GL_ALL_COMPLETED_NV:
        return "GL_ALL_COMPLETED_NV";
    case GL_FENCE_STATUS_NV:
        return "GL_FENCE_STATUS_NV";
    case GL_FENCE_CONDITION_NV:
        return "GL_FENCE_CONDITION_NV";
#ifndef GL_ES_VERSION_3_0
    case GL_TEXTURE_RECTANGLE:
        return "GL_TEXTURE_RECTANGLE";
    case GL_TEXTURE_BINDING_RECTANGLE:
        return "GL_TEXTURE_BINDING_RECTANGLE";
    case GL_PROXY_TEXTURE_RECTANGLE:
        return "GL_PROXY_TEXTURE_RECTANGLE";
    case GL_MAX_RECTANGLE_TEXTURE_SIZE:
        return "GL_MAX_RECTANGLE_TEXTURE_SIZE";
#endif
    case GL_DEPTH_STENCIL:
        return "GL_DEPTH_STENCIL";
    case GL_UNSIGNED_INT_24_8:
        return "GL_UNSIGNED_INT_24_8";
    case GL_MAX_TEXTURE_LOD_BIAS:
        return "GL_MAX_TEXTURE_LOD_BIAS";
    case GL_TEXTURE_MAX_ANISOTROPY_EXT:
        return "GL_TEXTURE_MAX_ANISOTROPY_EXT";
    case GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT:
        return "GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT";
#ifndef GL_ES_VERSION_3_0
    case GL_TEXTURE_FILTER_CONTROL:
        return "GL_TEXTURE_FILTER_CONTROL";
    case GL_TEXTURE_LOD_BIAS:
        return "GL_TEXTURE_LOD_BIAS";
    case GL_MODELVIEW1_STACK_DEPTH_EXT:
        return "GL_MODELVIEW1_STACK_DEPTH_EXT";
    case GL_COMBINE4_NV:
        return "GL_COMBINE4_NV";
    case GL_MAX_SHININESS_NV:
        return "GL_MAX_SHININESS_NV";
    case GL_MAX_SPOT_EXPONENT_NV:
        return "GL_MAX_SPOT_EXPONENT_NV";
    case GL_MODELVIEW1_MATRIX_EXT:
        return "GL_MODELVIEW1_MATRIX_EXT";
#endif
    case GL_INCR_WRAP:
        return "GL_INCR_WRAP";
    case GL_DECR_WRAP:
        return "GL_DECR_WRAP";
#ifndef GL_ES_VERSION_3_0
    case GL_VERTEX_WEIGHTING_EXT:
        return "GL_VERTEX_WEIGHTING_EXT";
    case GL_MODELVIEW1_ARB:
        return "GL_MODELVIEW1_ARB";
    case GL_CURRENT_VERTEX_WEIGHT_EXT:
        return "GL_CURRENT_VERTEX_WEIGHT_EXT";
    case GL_VERTEX_WEIGHT_ARRAY_EXT:
        return "GL_VERTEX_WEIGHT_ARRAY_EXT";
    case GL_VERTEX_WEIGHT_ARRAY_SIZE_EXT:
        return "GL_VERTEX_WEIGHT_ARRAY_SIZE_EXT";
    case GL_VERTEX_WEIGHT_ARRAY_TYPE_EXT:
        return "GL_VERTEX_WEIGHT_ARRAY_TYPE_EXT";
    case GL_VERTEX_WEIGHT_ARRAY_STRIDE_EXT:
        return "GL_VERTEX_WEIGHT_ARRAY_STRIDE_EXT";
    case GL_VERTEX_WEIGHT_ARRAY_POINTER_EXT:
        return "GL_VERTEX_WEIGHT_ARRAY_POINTER_EXT";
    case GL_NORMAL_MAP:
        return "GL_NORMAL_MAP";
    case GL_REFLECTION_MAP:
        return "GL_REFLECTION_MAP";
#endif
    case GL_TEXTURE_CUBE_MAP:
        return "GL_TEXTURE_CUBE_MAP";
    case GL_TEXTURE_BINDING_CUBE_MAP:
        return "GL_TEXTURE_BINDING_CUBE_MAP";
    case GL_TEXTURE_CUBE_MAP_POSITIVE_X:
        return "GL_TEXTURE_CUBE_MAP_POSITIVE_X";
    case GL_TEXTURE_CUBE_MAP_NEGATIVE_X:
        return "GL_TEXTURE_CUBE_MAP_NEGATIVE_X";
    case GL_TEXTURE_CUBE_MAP_POSITIVE_Y:
        return "GL_TEXTURE_CUBE_MAP_POSITIVE_Y";
    case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y:
        return "GL_TEXTURE_CUBE_MAP_NEGATIVE_Y";
    case GL_TEXTURE_CUBE_MAP_POSITIVE_Z:
        return "GL_TEXTURE_CUBE_MAP_POSITIVE_Z";
    case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z:
        return "GL_TEXTURE_CUBE_MAP_NEGATIVE_Z";
#ifndef GL_ES_VERSION_3_0
    case GL_PROXY_TEXTURE_CUBE_MAP:
        return "GL_PROXY_TEXTURE_CUBE_MAP";
#endif
    case GL_MAX_CUBE_MAP_TEXTURE_SIZE:
        return "GL_MAX_CUBE_MAP_TEXTURE_SIZE";
    case GL_VERTEX_ARRAY_BINDING:
        return "GL_VERTEX_ARRAY_BINDING";
    case GL_UNSIGNED_SHORT_8_8_APPLE:
        return "GL_UNSIGNED_SHORT_8_8_APPLE";
    case GL_UNSIGNED_SHORT_8_8_REV_APPLE:
        return "GL_UNSIGNED_SHORT_8_8_REV_APPLE";
    case GL_VERTEX_ATTRIB_ARRAY_ENABLED:
        return "GL_VERTEX_ATTRIB_ARRAY_ENABLED";
    case GL_VERTEX_ATTRIB_ARRAY_SIZE:
        return "GL_VERTEX_ATTRIB_ARRAY_SIZE";
    case GL_VERTEX_ATTRIB_ARRAY_STRIDE:
        return "GL_VERTEX_ATTRIB_ARRAY_STRIDE";
    case GL_VERTEX_ATTRIB_ARRAY_TYPE:
        return "GL_VERTEX_ATTRIB_ARRAY_TYPE";
    case GL_CURRENT_VERTEX_ATTRIB:
        return "GL_CURRENT_VERTEX_ATTRIB";
    case GL_VERTEX_ATTRIB_ARRAY_POINTER:
        return "GL_VERTEX_ATTRIB_ARRAY_POINTER";
    case GL_NUM_COMPRESSED_TEXTURE_FORMATS:
        return "GL_NUM_COMPRESSED_TEXTURE_FORMATS";
    case GL_COMPRESSED_TEXTURE_FORMATS:
        return "GL_COMPRESSED_TEXTURE_FORMATS";

    case GL_PROGRAM_BINARY_LENGTH:
        return "GL_PROGRAM_BINARY_LENGTH";

    case GL_BUFFER_SIZE:
        return "GL_BUFFER_SIZE";
    case GL_BUFFER_USAGE:
        return "GL_BUFFER_USAGE";

    case GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD:
        return "GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD";
    case GL_3DC_X_AMD:
        return "GL_3DC_X_AMD";
    case GL_3DC_XY_AMD:
        return "GL_3DC_XY_AMD";
    case GL_NUM_PROGRAM_BINARY_FORMATS:
        return "GL_NUM_PROGRAM_BINARY_FORMATS";
    case GL_PROGRAM_BINARY_FORMATS:
        return "GL_PROGRAM_BINARY_FORMATS";
    case GL_STENCIL_BACK_FUNC:
        return "GL_STENCIL_BACK_FUNC";
    case GL_STENCIL_BACK_FAIL:
        return "GL_STENCIL_BACK_FAIL";
    case GL_STENCIL_BACK_PASS_DEPTH_FAIL:
        return "GL_STENCIL_BACK_PASS_DEPTH_FAIL";
    case GL_STENCIL_BACK_PASS_DEPTH_PASS:
        return "GL_STENCIL_BACK_PASS_DEPTH_PASS";

    case GL_RGBA32F:
        return "GL_RGBA32F";
    case GL_RGB32F:
        return "GL_RGB32F";

    case GL_RGBA16F:
        return "GL_RGBA16F";
    case GL_RGB16F:
        return "GL_RGB16F";

    case GL_MAX_DRAW_BUFFERS:
        return "GL_MAX_DRAW_BUFFERS";
    case GL_DRAW_BUFFER0:
        return "GL_DRAW_BUFFER0";
    case GL_DRAW_BUFFER1:
        return "GL_DRAW_BUFFER1";
    case GL_DRAW_BUFFER2:
        return "GL_DRAW_BUFFER2";
    case GL_DRAW_BUFFER3:
        return "GL_DRAW_BUFFER3";
    case GL_DRAW_BUFFER4:
        return "GL_DRAW_BUFFER4";
    case GL_DRAW_BUFFER5:
        return "GL_DRAW_BUFFER5";
    case GL_DRAW_BUFFER6:
        return "GL_DRAW_BUFFER6";
    case GL_DRAW_BUFFER7:
        return "GL_DRAW_BUFFER7";
    case GL_DRAW_BUFFER8:
        return "GL_DRAW_BUFFER8";
    case GL_DRAW_BUFFER9:
        return "GL_DRAW_BUFFER9";
    case GL_DRAW_BUFFER10:
        return "GL_DRAW_BUFFER10";
    case GL_DRAW_BUFFER11:
        return "GL_DRAW_BUFFER11";
    case GL_DRAW_BUFFER12:
        return "GL_DRAW_BUFFER12";
    case GL_DRAW_BUFFER13:
        return "GL_DRAW_BUFFER13";
    case GL_DRAW_BUFFER14:
        return "GL_DRAW_BUFFER14";
    case GL_DRAW_BUFFER15:
        return "GL_DRAW_BUFFER15";

    case GL_BLEND_EQUATION_ALPHA:
        return "GL_BLEND_EQUATION_ALPHA";

    case GL_TEXTURE_COMPARE_MODE:
        return "GL_TEXTURE_COMPARE_MODE";
    case GL_TEXTURE_COMPARE_FUNC:
        return "GL_TEXTURE_COMPARE_FUNC";
    case GL_COMPARE_REF_TO_TEXTURE:
        return "GL_COMPARE_REF_TO_TEXTURE";

    case GL_CURRENT_QUERY:
        return "GL_CURRENT_QUERY";
    case GL_QUERY_RESULT:
        return "GL_QUERY_RESULT";
    case GL_QUERY_RESULT_AVAILABLE:
        return "GL_QUERY_RESULT_AVAILABLE";
    case GL_MAX_VERTEX_ATTRIBS:
        return "GL_MAX_VERTEX_ATTRIBS";
    case GL_VERTEX_ATTRIB_ARRAY_NORMALIZED:
        return "GL_VERTEX_ATTRIB_ARRAY_NORMALIZED";

    case GL_MAX_TEXTURE_IMAGE_UNITS:
        return "GL_MAX_TEXTURE_IMAGE_UNITS";

    case GL_ARRAY_BUFFER:
        return "GL_ARRAY_BUFFER";
    case GL_ELEMENT_ARRAY_BUFFER:
        return "GL_ELEMENT_ARRAY_BUFFER";
    case GL_ARRAY_BUFFER_BINDING:
        return "GL_ARRAY_BUFFER_BINDING";
    case GL_ELEMENT_ARRAY_BUFFER_BINDING:
        return "GL_ELEMENT_ARRAY_BUFFER_BINDING";

    case GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING:
        return "GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING";

    case GL_BUFFER_MAPPED:
        return "GL_BUFFER_MAPPED";
    case GL_BUFFER_MAP_POINTER:
        return "GL_BUFFER_MAP_POINTER";

    case GL_STREAM_DRAW:
        return "GL_STREAM_DRAW";
    case GL_STREAM_READ:
        return "GL_STREAM_READ";
    case GL_STREAM_COPY:
        return "GL_STREAM_COPY";
    case GL_STATIC_DRAW:
        return "GL_STATIC_DRAW";
    case GL_STATIC_READ:
        return "GL_STATIC_READ";
    case GL_STATIC_COPY:
        return "GL_STATIC_COPY";
    case GL_DYNAMIC_DRAW:
        return "GL_DYNAMIC_DRAW";
    case GL_DYNAMIC_READ:
        return "GL_DYNAMIC_READ";
    case GL_DYNAMIC_COPY:
        return "GL_DYNAMIC_COPY";
    case GL_PIXEL_PACK_BUFFER:
        return "GL_PIXEL_PACK_BUFFER";
    case GL_PIXEL_UNPACK_BUFFER:
        return "GL_PIXEL_UNPACK_BUFFER";
    case GL_PIXEL_PACK_BUFFER_BINDING:
        return "GL_PIXEL_PACK_BUFFER_BINDING";
    case GL_ETC1_SRGB8_NV:
        return "GL_ETC1_SRGB8_NV";
    case GL_PIXEL_UNPACK_BUFFER_BINDING:
        return "GL_PIXEL_UNPACK_BUFFER_BINDING";
    case GL_DEPTH24_STENCIL8:
        return "GL_DEPTH24_STENCIL8";

    case GL_VERTEX_ATTRIB_ARRAY_INTEGER:
        return "GL_VERTEX_ATTRIB_ARRAY_INTEGER";
    case GL_VERTEX_ATTRIB_ARRAY_DIVISOR:
        return "GL_VERTEX_ATTRIB_ARRAY_DIVISOR";
    case GL_MAX_ARRAY_TEXTURE_LAYERS:
        return "GL_MAX_ARRAY_TEXTURE_LAYERS";
    case GL_MIN_PROGRAM_TEXEL_OFFSET:
        return "GL_MIN_PROGRAM_TEXEL_OFFSET";
    case GL_MAX_PROGRAM_TEXEL_OFFSET:
        return "GL_MAX_PROGRAM_TEXEL_OFFSET";

    case GL_SAMPLER_BINDING:
        return "GL_SAMPLER_BINDING";

    case GL_UNIFORM_BUFFER:
        return "GL_UNIFORM_BUFFER";

    case GL_RGB_422_APPLE:
        return "GL_RGB_422_APPLE";
    case GL_UNIFORM_BUFFER_BINDING:
        return "GL_UNIFORM_BUFFER_BINDING";
    case GL_UNIFORM_BUFFER_START:
        return "GL_UNIFORM_BUFFER_START";
    case GL_UNIFORM_BUFFER_SIZE:
        return "GL_UNIFORM_BUFFER_SIZE";
    case GL_MAX_VERTEX_UNIFORM_BLOCKS:
        return "GL_MAX_VERTEX_UNIFORM_BLOCKS";
    case GL_MAX_FRAGMENT_UNIFORM_BLOCKS:
        return "GL_MAX_FRAGMENT_UNIFORM_BLOCKS";
    case GL_MAX_COMBINED_UNIFORM_BLOCKS:
        return "GL_MAX_COMBINED_UNIFORM_BLOCKS";
    case GL_MAX_UNIFORM_BUFFER_BINDINGS:
        return "GL_MAX_UNIFORM_BUFFER_BINDINGS";
    case GL_MAX_UNIFORM_BLOCK_SIZE:
        return "GL_MAX_UNIFORM_BLOCK_SIZE";
    case GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS:
        return "GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS";
    case GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS:
        return "GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS";
    case GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT:
        return "GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT";
    case GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH:
        return "GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH";
    case GL_ACTIVE_UNIFORM_BLOCKS:
        return "GL_ACTIVE_UNIFORM_BLOCKS";
    case GL_UNIFORM_TYPE:
        return "GL_UNIFORM_TYPE";
    case GL_UNIFORM_SIZE:
        return "GL_UNIFORM_SIZE";
    case GL_UNIFORM_NAME_LENGTH:
        return "GL_UNIFORM_NAME_LENGTH";
    case GL_UNIFORM_BLOCK_INDEX:
        return "GL_UNIFORM_BLOCK_INDEX";
    case GL_UNIFORM_OFFSET:
        return "GL_UNIFORM_OFFSET";
    case GL_UNIFORM_ARRAY_STRIDE:
        return "GL_UNIFORM_ARRAY_STRIDE";
    case GL_UNIFORM_MATRIX_STRIDE:
        return "GL_UNIFORM_MATRIX_STRIDE";
    case GL_UNIFORM_IS_ROW_MAJOR:
        return "GL_UNIFORM_IS_ROW_MAJOR";
    case GL_UNIFORM_BLOCK_BINDING:
        return "GL_UNIFORM_BLOCK_BINDING";
    case GL_UNIFORM_BLOCK_DATA_SIZE:
        return "GL_UNIFORM_BLOCK_DATA_SIZE";
    case GL_UNIFORM_BLOCK_NAME_LENGTH:
        return "GL_UNIFORM_BLOCK_NAME_LENGTH";
    case GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS:
        return "GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS";
    case GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES:
        return "GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES";
    case GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER:
        return "GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER";
    case GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER:
        return "GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER";
    case GL_TEXTURE_SRGB_DECODE_EXT:
        return "GL_TEXTURE_SRGB_DECODE_EXT";
    case GL_DECODE_EXT:
        return "GL_DECODE_EXT";
    case GL_SKIP_DECODE_EXT:
        return "GL_SKIP_DECODE_EXT";
    case GL_PROGRAM_PIPELINE_OBJECT_EXT:
        return "GL_PROGRAM_PIPELINE_OBJECT_EXT";
    case GL_RGB_RAW_422_APPLE:
        return "GL_RGB_RAW_422_APPLE";
    case GL_FRAGMENT_SHADER_DISCARDS_SAMPLES_EXT:
        return "GL_FRAGMENT_SHADER_DISCARDS_SAMPLES_EXT";
    case GL_SYNC_OBJECT_APPLE:
        return "GL_SYNC_OBJECT_APPLE";
    case GL_COMPRESSED_SRGB_PVRTC_2BPPV1_EXT:
        return "GL_COMPRESSED_SRGB_PVRTC_2BPPV1_EXT";
    case GL_COMPRESSED_SRGB_PVRTC_4BPPV1_EXT:
        return "GL_COMPRESSED_SRGB_PVRTC_4BPPV1_EXT";
    case GL_COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV1_EXT:
        return "GL_COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV1_EXT";
    case GL_COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV1_EXT:
        return "GL_COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV1_EXT";
    case GL_FRAGMENT_SHADER:
        return "GL_FRAGMENT_SHADER";
    case GL_VERTEX_SHADER:
        return "GL_VERTEX_SHADER";
    case GL_MAX_FRAGMENT_UNIFORM_COMPONENTS:
        return "GL_MAX_FRAGMENT_UNIFORM_COMPONENTS";
    case GL_MAX_VERTEX_UNIFORM_COMPONENTS:
        return "GL_MAX_VERTEX_UNIFORM_COMPONENTS";
    case GL_MAX_VARYING_COMPONENTS:
        return "GL_MAX_VARYING_COMPONENTS";
    case GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS:
        return "GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS";
    case GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS:
        return "GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS";
    case GL_SHADER_TYPE:
        return "GL_SHADER_TYPE";
    case GL_FLOAT_VEC2:
        return "GL_FLOAT_VEC2";
    case GL_FLOAT_VEC3:
        return "GL_FLOAT_VEC3";
    case GL_FLOAT_VEC4:
        return "GL_FLOAT_VEC4";
    case GL_INT_VEC2:
        return "GL_INT_VEC2";
    case GL_INT_VEC3:
        return "GL_INT_VEC3";
    case GL_INT_VEC4:
        return "GL_INT_VEC4";
    case GL_BOOL:
        return "GL_BOOL";
    case GL_BOOL_VEC2:
        return "GL_BOOL_VEC2";
    case GL_BOOL_VEC3:
        return "GL_BOOL_VEC3";
    case GL_BOOL_VEC4:
        return "GL_BOOL_VEC4";
    case GL_FLOAT_MAT2:
        return "GL_FLOAT_MAT2";
    case GL_FLOAT_MAT3:
        return "GL_FLOAT_MAT3";
    case GL_FLOAT_MAT4:
        return "GL_FLOAT_MAT4";
    case GL_SAMPLER_2D:
        return "GL_SAMPLER_2D";
    case GL_SAMPLER_3D:
        return "GL_SAMPLER_3D";
    case GL_SAMPLER_CUBE:
        return "GL_SAMPLER_CUBE";
    case GL_SAMPLER_2D_SHADOW:
        return "GL_SAMPLER_2D_SHADOW";
    case GL_FLOAT_MAT2x3:
        return "GL_FLOAT_MAT2x3";
    case GL_FLOAT_MAT2x4:
        return "GL_FLOAT_MAT2x4";
    case GL_FLOAT_MAT3x2:
        return "GL_FLOAT_MAT3x2";
    case GL_FLOAT_MAT3x4:
        return "GL_FLOAT_MAT3x4";
    case GL_FLOAT_MAT4x2:
        return "GL_FLOAT_MAT4x2";
    case GL_FLOAT_MAT4x3:
        return "GL_FLOAT_MAT4x3";
    case GL_DELETE_STATUS:
        return "GL_DELETE_STATUS";
    case GL_COMPILE_STATUS:
        return "GL_COMPILE_STATUS";
    case GL_LINK_STATUS:
        return "GL_LINK_STATUS";
    case GL_VALIDATE_STATUS:
        return "GL_VALIDATE_STATUS";
    case GL_INFO_LOG_LENGTH:
        return "GL_INFO_LOG_LENGTH";
    case GL_ATTACHED_SHADERS:
        return "GL_ATTACHED_SHADERS";
    case GL_ACTIVE_UNIFORMS:
        return "GL_ACTIVE_UNIFORMS";
    case GL_ACTIVE_UNIFORM_MAX_LENGTH:
        return "GL_ACTIVE_UNIFORM_MAX_LENGTH";
    case GL_SHADER_SOURCE_LENGTH:
        return "GL_SHADER_SOURCE_LENGTH";
    case GL_ACTIVE_ATTRIBUTES:
        return "GL_ACTIVE_ATTRIBUTES";
    case GL_ACTIVE_ATTRIBUTE_MAX_LENGTH:
        return "GL_ACTIVE_ATTRIBUTE_MAX_LENGTH";
    case GL_FRAGMENT_SHADER_DERIVATIVE_HINT:
        return "GL_FRAGMENT_SHADER_DERIVATIVE_HINT";
    case GL_SHADING_LANGUAGE_VERSION:
        return "GL_SHADING_LANGUAGE_VERSION";
    case GL_CURRENT_PROGRAM:
        return "GL_CURRENT_PROGRAM";
    case GL_PALETTE4_RGB8_OES:
        return "GL_PALETTE4_RGB8_OES";
    case GL_PALETTE4_RGBA8_OES:
        return "GL_PALETTE4_RGBA8_OES";
    case GL_PALETTE4_R5_G6_B5_OES:
        return "GL_PALETTE4_R5_G6_B5_OES";
    case GL_PALETTE4_RGBA4_OES:
        return "GL_PALETTE4_RGBA4_OES";
    case GL_PALETTE4_RGB5_A1_OES:
        return "GL_PALETTE4_RGB5_A1_OES";
    case GL_PALETTE8_RGB8_OES:
        return "GL_PALETTE8_RGB8_OES";
    case GL_PALETTE8_RGBA8_OES:
        return "GL_PALETTE8_RGBA8_OES";
    case GL_PALETTE8_R5_G6_B5_OES:
        return "GL_PALETTE8_R5_G6_B5_OES";
    case GL_PALETTE8_RGBA4_OES:
        return "GL_PALETTE8_RGBA4_OES";
    case GL_PALETTE8_RGB5_A1_OES:
        return "GL_PALETTE8_RGB5_A1_OES";
    case GL_IMPLEMENTATION_COLOR_READ_TYPE:
        return "GL_IMPLEMENTATION_COLOR_READ_TYPE";
    case GL_IMPLEMENTATION_COLOR_READ_FORMAT:
        return "GL_IMPLEMENTATION_COLOR_READ_FORMAT";
    case GL_COUNTER_TYPE_AMD:
        return "GL_COUNTER_TYPE_AMD";
    case GL_COUNTER_RANGE_AMD:
        return "GL_COUNTER_RANGE_AMD";
    case GL_UNSIGNED_INT64_AMD:
        return "GL_UNSIGNED_INT64_AMD";
    case GL_PERCENTAGE_AMD:
        return "GL_PERCENTAGE_AMD";
    case GL_PERFMON_RESULT_AVAILABLE_AMD:
        return "GL_PERFMON_RESULT_AVAILABLE_AMD";
    case GL_PERFMON_RESULT_SIZE_AMD:
        return "GL_PERFMON_RESULT_SIZE_AMD";
    case GL_PERFMON_RESULT_AMD:
        return "GL_PERFMON_RESULT_AMD";
    case GL_SAMPLER_EXTERNAL_2D_Y2Y_EXT:
        return "GL_SAMPLER_EXTERNAL_2D_Y2Y_EXT";

    case GL_UNSIGNED_NORMALIZED:
        return "GL_UNSIGNED_NORMALIZED";

    case GL_TEXTURE_2D_ARRAY:
        return "GL_TEXTURE_2D_ARRAY";

    case GL_TEXTURE_BINDING_2D_ARRAY:
        return "GL_TEXTURE_BINDING_2D_ARRAY";

    case GL_ANY_SAMPLES_PASSED:
        return "GL_ANY_SAMPLES_PASSED";
    case GL_R11F_G11F_B10F:
        return "GL_R11F_G11F_B10F";
    case GL_UNSIGNED_INT_10F_11F_11F_REV:
        return "GL_UNSIGNED_INT_10F_11F_11F_REV";
    case GL_RGB9_E5:
        return "GL_RGB9_E5";
    case GL_UNSIGNED_INT_5_9_9_9_REV:
        return "GL_UNSIGNED_INT_5_9_9_9_REV";
    case GL_SRGB:
        return "GL_SRGB";
    case GL_SRGB8:
        return "GL_SRGB8";
    case GL_SRGB8_ALPHA8:
        return "GL_SRGB8_ALPHA8";

    case GL_COMPRESSED_SRGB_S3TC_DXT1_EXT:
        return "GL_COMPRESSED_SRGB_S3TC_DXT1_EXT";
    case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT:
        return "GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT";
    case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT:
        return "GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT";
    case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT:
        return "GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT";

    case GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH:
        return "GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH";

    case GL_TRANSFORM_FEEDBACK_BUFFER_MODE:
        return "GL_TRANSFORM_FEEDBACK_BUFFER_MODE";
    case GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS:
        return "GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS";
    case GL_TRANSFORM_FEEDBACK_VARYINGS:
        return "GL_TRANSFORM_FEEDBACK_VARYINGS";
    case GL_TRANSFORM_FEEDBACK_BUFFER_START:
        return "GL_TRANSFORM_FEEDBACK_BUFFER_START";
    case GL_TRANSFORM_FEEDBACK_BUFFER_SIZE:
        return "GL_TRANSFORM_FEEDBACK_BUFFER_SIZE";
    case GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN:
        return "GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN";
    case GL_RASTERIZER_DISCARD:
        return "GL_RASTERIZER_DISCARD";
    case GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS:
        return "GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS";
    case GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS:
        return "GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS";
    case GL_INTERLEAVED_ATTRIBS:
        return "GL_INTERLEAVED_ATTRIBS";
    case GL_SEPARATE_ATTRIBS:
        return "GL_SEPARATE_ATTRIBS";
    case GL_TRANSFORM_FEEDBACK_BUFFER:
        return "GL_TRANSFORM_FEEDBACK_BUFFER";
    case GL_TRANSFORM_FEEDBACK_BUFFER_BINDING:
        return "GL_TRANSFORM_FEEDBACK_BUFFER_BINDING";
    case GL_ATC_RGB_AMD:
        return "GL_ATC_RGB_AMD";
    case GL_ATC_RGBA_EXPLICIT_ALPHA_AMD:
        return "GL_ATC_RGBA_EXPLICIT_ALPHA_AMD";
    case GL_STENCIL_BACK_REF:
        return "GL_STENCIL_BACK_REF";
    case GL_STENCIL_BACK_VALUE_MASK:
        return "GL_STENCIL_BACK_VALUE_MASK";
    case GL_STENCIL_BACK_WRITEMASK:
        return "GL_STENCIL_BACK_WRITEMASK";
    case GL_DRAW_FRAMEBUFFER_BINDING:
        return "GL_DRAW_FRAMEBUFFER_BINDING";
    case GL_RENDERBUFFER_BINDING:
        return "GL_RENDERBUFFER_BINDING";
    case GL_READ_FRAMEBUFFER:
        return "GL_READ_FRAMEBUFFER";
    case GL_DRAW_FRAMEBUFFER:
        return "GL_DRAW_FRAMEBUFFER";
    case GL_READ_FRAMEBUFFER_BINDING:
        return "GL_READ_FRAMEBUFFER_BINDING";
    case GL_RENDERBUFFER_SAMPLES:
        return "GL_RENDERBUFFER_SAMPLES";
    case GL_DEPTH_COMPONENT32F:
        return "GL_DEPTH_COMPONENT32F";
    case GL_DEPTH32F_STENCIL8:
        return "GL_DEPTH32F_STENCIL8";
    case GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE:
        return "GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE";
    case GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME:
        return "GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME";
    case GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL:
        return "GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL";
    case GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE:
        return "GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE";
    case GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER:
        return "GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER";
    case GL_FRAMEBUFFER_COMPLETE:
        return "GL_FRAMEBUFFER_COMPLETE";
    case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
        return "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT";
    case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
        return "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT";
    case GL_FRAMEBUFFER_UNSUPPORTED:
        return "GL_FRAMEBUFFER_UNSUPPORTED";
    case GL_MAX_COLOR_ATTACHMENTS:
        return "GL_MAX_COLOR_ATTACHMENTS";
    case GL_COLOR_ATTACHMENT0:
        return "GL_COLOR_ATTACHMENT0";
    case GL_COLOR_ATTACHMENT1:
        return "GL_COLOR_ATTACHMENT1";
    case GL_COLOR_ATTACHMENT2:
        return "GL_COLOR_ATTACHMENT2";
    case GL_COLOR_ATTACHMENT3:
        return "GL_COLOR_ATTACHMENT3";
    case GL_COLOR_ATTACHMENT4:
        return "GL_COLOR_ATTACHMENT4";
    case GL_COLOR_ATTACHMENT5:
        return "GL_COLOR_ATTACHMENT5";
    case GL_COLOR_ATTACHMENT6:
        return "GL_COLOR_ATTACHMENT6";
    case GL_COLOR_ATTACHMENT7:
        return "GL_COLOR_ATTACHMENT7";
    case GL_COLOR_ATTACHMENT8:
        return "GL_COLOR_ATTACHMENT8";
    case GL_COLOR_ATTACHMENT9:
        return "GL_COLOR_ATTACHMENT9";
    case GL_COLOR_ATTACHMENT10:
        return "GL_COLOR_ATTACHMENT10";
    case GL_COLOR_ATTACHMENT11:
        return "GL_COLOR_ATTACHMENT11";
    case GL_COLOR_ATTACHMENT12:
        return "GL_COLOR_ATTACHMENT12";
    case GL_COLOR_ATTACHMENT13:
        return "GL_COLOR_ATTACHMENT13";
    case GL_COLOR_ATTACHMENT14:
        return "GL_COLOR_ATTACHMENT14";
    case GL_COLOR_ATTACHMENT15:
        return "GL_COLOR_ATTACHMENT15";
    case GL_COLOR_ATTACHMENT16:
        return "GL_COLOR_ATTACHMENT16";
    case GL_COLOR_ATTACHMENT17:
        return "GL_COLOR_ATTACHMENT17";
    case GL_COLOR_ATTACHMENT18:
        return "GL_COLOR_ATTACHMENT18";
    case GL_COLOR_ATTACHMENT19:
        return "GL_COLOR_ATTACHMENT19";
    case GL_COLOR_ATTACHMENT20:
        return "GL_COLOR_ATTACHMENT20";
    case GL_COLOR_ATTACHMENT21:
        return "GL_COLOR_ATTACHMENT21";
    case GL_COLOR_ATTACHMENT22:
        return "GL_COLOR_ATTACHMENT22";
    case GL_COLOR_ATTACHMENT23:
        return "GL_COLOR_ATTACHMENT23";
    case GL_COLOR_ATTACHMENT24:
        return "GL_COLOR_ATTACHMENT24";
    case GL_COLOR_ATTACHMENT25:
        return "GL_COLOR_ATTACHMENT25";
    case GL_COLOR_ATTACHMENT26:
        return "GL_COLOR_ATTACHMENT26";
    case GL_COLOR_ATTACHMENT27:
        return "GL_COLOR_ATTACHMENT27";
    case GL_COLOR_ATTACHMENT28:
        return "GL_COLOR_ATTACHMENT28";
    case GL_COLOR_ATTACHMENT29:
        return "GL_COLOR_ATTACHMENT29";
    case GL_COLOR_ATTACHMENT30:
        return "GL_COLOR_ATTACHMENT30";
    case GL_COLOR_ATTACHMENT31:
        return "GL_COLOR_ATTACHMENT31";
    case GL_DEPTH_ATTACHMENT:
        return "GL_DEPTH_ATTACHMENT";
    case GL_STENCIL_ATTACHMENT:
        return "GL_STENCIL_ATTACHMENT";
    case GL_FRAMEBUFFER:
        return "GL_FRAMEBUFFER";
    case GL_RENDERBUFFER:
        return "GL_RENDERBUFFER";
    case GL_RENDERBUFFER_WIDTH:
        return "GL_RENDERBUFFER_WIDTH";
    case GL_RENDERBUFFER_HEIGHT:
        return "GL_RENDERBUFFER_HEIGHT";
    case GL_RENDERBUFFER_INTERNAL_FORMAT:
        return "GL_RENDERBUFFER_INTERNAL_FORMAT";
    case GL_STENCIL_INDEX8:
        return "GL_STENCIL_INDEX8";
    case GL_RENDERBUFFER_RED_SIZE:
        return "GL_RENDERBUFFER_RED_SIZE";
    case GL_RENDERBUFFER_GREEN_SIZE:
        return "GL_RENDERBUFFER_GREEN_SIZE";
    case GL_RENDERBUFFER_BLUE_SIZE:
        return "GL_RENDERBUFFER_BLUE_SIZE";
    case GL_RENDERBUFFER_ALPHA_SIZE:
        return "GL_RENDERBUFFER_ALPHA_SIZE";
    case GL_RENDERBUFFER_DEPTH_SIZE:
        return "GL_RENDERBUFFER_DEPTH_SIZE";
    case GL_RENDERBUFFER_STENCIL_SIZE:
        return "GL_RENDERBUFFER_STENCIL_SIZE";
    case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
        return "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE";
    case GL_MAX_SAMPLES:
        return "GL_MAX_SAMPLES";
    case GL_HALF_FLOAT_OES:
        return "GL_HALF_FLOAT_OES";
    case GL_RGB565:
        return "GL_RGB565";
    case GL_ETC1_RGB8_OES:
        return "GL_ETC1_RGB8_OES";
    case GL_TEXTURE_EXTERNAL_OES:
        return "GL_TEXTURE_EXTERNAL_OES";
    case GL_SAMPLER_EXTERNAL_OES:
        return "GL_SAMPLER_EXTERNAL_OES";
    case GL_TEXTURE_BINDING_EXTERNAL_OES:
        return "GL_TEXTURE_BINDING_EXTERNAL_OES";
    case GL_REQUIRED_TEXTURE_IMAGE_UNITS_OES:
        return "GL_REQUIRED_TEXTURE_IMAGE_UNITS_OES";
    case GL_PRIMITIVE_RESTART_FIXED_INDEX:
        return "GL_PRIMITIVE_RESTART_FIXED_INDEX";
    case GL_ANY_SAMPLES_PASSED_CONSERVATIVE:
        return "GL_ANY_SAMPLES_PASSED_CONSERVATIVE";
    case GL_MAX_ELEMENT_INDEX:
        return "GL_MAX_ELEMENT_INDEX";
    case GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_SAMPLES_EXT:
        return "GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_SAMPLES_EXT";
    case GL_RGBA32UI:
        return "GL_RGBA32UI";
    case GL_RGB32UI:
        return "GL_RGB32UI";
    case GL_RGBA16UI:
        return "GL_RGBA16UI";
    case GL_RGB16UI:
        return "GL_RGB16UI";
    case GL_RGBA8UI:
        return "GL_RGBA8UI";
    case GL_RGB8UI:
        return "GL_RGB8UI";

    case GL_RGBA32I:
        return "GL_RGBA32I";
    case GL_RGB32I:
        return "GL_RGB32I";

    case GL_RGBA16I:
        return "GL_RGBA16I";
    case GL_RGB16I:
        return "GL_RGB16I";

    case GL_RGBA8I:
        return "GL_RGBA8I";
    case GL_RGB8I:
        return "GL_RGB8I";

    case GL_RED_INTEGER:
        return "GL_RED_INTEGER";

    case GL_RGB_INTEGER:
        return "GL_RGB_INTEGER";
    case GL_RGBA_INTEGER:
        return "GL_RGBA_INTEGER";

    case GL_INT_2_10_10_10_REV:
        return "GL_INT_2_10_10_10_REV";

    case GL_FLOAT_32_UNSIGNED_INT_24_8_REV:
        return "GL_FLOAT_32_UNSIGNED_INT_24_8_REV";

    case GL_SAMPLER_2D_ARRAY:
        return "GL_SAMPLER_2D_ARRAY";
    case GL_SAMPLER_2D_ARRAY_SHADOW:
        return "GL_SAMPLER_2D_ARRAY_SHADOW";
    case GL_SAMPLER_CUBE_SHADOW:
        return "GL_SAMPLER_CUBE_SHADOW";
    case GL_UNSIGNED_INT_VEC2:
        return "GL_UNSIGNED_INT_VEC2";
    case GL_UNSIGNED_INT_VEC3:
        return "GL_UNSIGNED_INT_VEC3";
    case GL_UNSIGNED_INT_VEC4:
        return "GL_UNSIGNED_INT_VEC4";
    case GL_INT_SAMPLER_2D:
        return "GL_INT_SAMPLER_2D";
    case GL_INT_SAMPLER_3D:
        return "GL_INT_SAMPLER_3D";
    case GL_INT_SAMPLER_CUBE:
        return "GL_INT_SAMPLER_CUBE";
    case GL_INT_SAMPLER_2D_ARRAY:
        return "GL_INT_SAMPLER_2D_ARRAY";
        return "GL_UNSIGNED_INT_SAMPLER_1D";
    case GL_UNSIGNED_INT_SAMPLER_2D:
        return "GL_UNSIGNED_INT_SAMPLER_2D";
    case GL_UNSIGNED_INT_SAMPLER_3D:
        return "GL_UNSIGNED_INT_SAMPLER_3D";
    case GL_UNSIGNED_INT_SAMPLER_CUBE:
        return "GL_UNSIGNED_INT_SAMPLER_CUBE";
    case GL_UNSIGNED_INT_SAMPLER_2D_ARRAY:
        return "GL_UNSIGNED_INT_SAMPLER_2D_ARRAY";

    case GL_LOW_FLOAT:
        return "GL_LOW_FLOAT";
    case GL_MEDIUM_FLOAT:
        return "GL_MEDIUM_FLOAT";
    case GL_HIGH_FLOAT:
        return "GL_HIGH_FLOAT";
    case GL_LOW_INT:
        return "GL_LOW_INT";
    case GL_MEDIUM_INT:
        return "GL_MEDIUM_INT";
    case GL_HIGH_INT:
        return "GL_HIGH_INT";
    case GL_UNSIGNED_INT_10_10_10_2_OES:
        return "GL_UNSIGNED_INT_10_10_10_2_OES";
    case GL_INT_10_10_10_2_OES:
        return "GL_INT_10_10_10_2_OES";
    case GL_SHADER_BINARY_FORMATS:
        return "GL_SHADER_BINARY_FORMATS";
    case GL_NUM_SHADER_BINARY_FORMATS:
        return "GL_NUM_SHADER_BINARY_FORMATS";
    case GL_SHADER_COMPILER:
        return "GL_SHADER_COMPILER";
    case GL_MAX_VERTEX_UNIFORM_VECTORS:
        return "GL_MAX_VERTEX_UNIFORM_VECTORS";
    case GL_MAX_VARYING_VECTORS:
        return "GL_MAX_VARYING_VECTORS";
    case GL_MAX_FRAGMENT_UNIFORM_VECTORS:
        return "GL_MAX_FRAGMENT_UNIFORM_VECTORS";

    case GL_POLYGON_OFFSET_CLAMP_EXT:
        return "GL_POLYGON_OFFSET_CLAMP_EXT";
    case GL_COLOR_SAMPLES_NV:
        return "GL_COLOR_SAMPLES_NV";
    case GL_TRANSFORM_FEEDBACK:
        return "GL_TRANSFORM_FEEDBACK";
    case GL_TRANSFORM_FEEDBACK_BINDING:
        return "GL_TRANSFORM_FEEDBACK_BINDING";

    case GL_DEPTH_COMPONENT16_NONLINEAR_NV:
        return "GL_DEPTH_COMPONENT16_NONLINEAR_NV";

    case GL_TEXTURE_SWIZZLE_R:
        return "GL_TEXTURE_SWIZZLE_R";
    case GL_TEXTURE_SWIZZLE_G:
        return "GL_TEXTURE_SWIZZLE_G";
    case GL_TEXTURE_SWIZZLE_B:
        return "GL_TEXTURE_SWIZZLE_B";
    case GL_TEXTURE_SWIZZLE_A:
        return "GL_TEXTURE_SWIZZLE_A";

    case GL_INCLUSIVE_EXT:
        return "GL_INCLUSIVE_EXT";
    case GL_EXCLUSIVE_EXT:
        return "GL_EXCLUSIVE_EXT";
    case GL_WINDOW_RECTANGLE_EXT:
        return "GL_WINDOW_RECTANGLE_EXT";
    case GL_WINDOW_RECTANGLE_MODE_EXT:
        return "GL_WINDOW_RECTANGLE_MODE_EXT";
    case GL_MAX_WINDOW_RECTANGLES_EXT:
        return "GL_MAX_WINDOW_RECTANGLES_EXT";
    case GL_NUM_WINDOW_RECTANGLES_EXT:
        return "GL_NUM_WINDOW_RECTANGLES_EXT";

    case GL_COPY_READ_BUFFER:
        return "GL_COPY_READ_BUFFER";
    case GL_COPY_WRITE_BUFFER:
        return "GL_COPY_WRITE_BUFFER";

    case GL_MALI_SHADER_BINARY_ARM:
        return "GL_MALI_SHADER_BINARY_ARM";
    case GL_MALI_PROGRAM_BINARY_ARM:
        return "GL_MALI_PROGRAM_BINARY_ARM";
    case GL_MAX_SHADER_PIXEL_LOCAL_STORAGE_FAST_SIZE_EXT:
        return "GL_MAX_SHADER_PIXEL_LOCAL_STORAGE_FAST_SIZE_EXT";
    case GL_SHADER_PIXEL_LOCAL_STORAGE_EXT:
        return "GL_SHADER_PIXEL_LOCAL_STORAGE_EXT";
    case GL_FETCH_PER_SAMPLE_ARM:
        return "GL_FETCH_PER_SAMPLE_ARM";
    case GL_FRAGMENT_SHADER_FRAMEBUFFER_FETCH_MRT_ARM:
        return "GL_FRAGMENT_SHADER_FRAMEBUFFER_FETCH_MRT_ARM";
    case GL_MAX_SHADER_PIXEL_LOCAL_STORAGE_SIZE_EXT:
        return "GL_MAX_SHADER_PIXEL_LOCAL_STORAGE_SIZE_EXT";
    case GL_TEXTURE_ASTC_DECODE_PRECISION_EXT:
        return "GL_TEXTURE_ASTC_DECODE_PRECISION_EXT";

    case GL_R8_SNORM:
        return "GL_R8_SNORM";
    case GL_RG8_SNORM:
        return "GL_RG8_SNORM";
    case GL_RGB8_SNORM:
        return "GL_RGB8_SNORM";
    case GL_RGBA8_SNORM:
        return "GL_RGBA8_SNORM";

    case GL_SIGNED_NORMALIZED:
        return "GL_SIGNED_NORMALIZED";

    case GL_PERFMON_GLOBAL_MODE_QCOM:
        return "GL_PERFMON_GLOBAL_MODE_QCOM";
    case GL_BINNING_CONTROL_HINT_QCOM:
        return "GL_BINNING_CONTROL_HINT_QCOM";
    case GL_CPU_OPTIMIZED_QCOM:
        return "GL_CPU_OPTIMIZED_QCOM";
    case GL_GPU_OPTIMIZED_QCOM:
        return "GL_GPU_OPTIMIZED_QCOM";
    case GL_RENDER_DIRECT_TO_FRAMEBUFFER_QCOM:
        return "GL_RENDER_DIRECT_TO_FRAMEBUFFER_QCOM";
    case GL_GPU_DISJOINT_EXT:
        return "GL_GPU_DISJOINT_EXT";
    case GL_SR8_EXT:
        return "GL_SR8_EXT";
    case GL_SRG8_EXT:
        return "GL_SRG8_EXT";
    case GL_SHADER_BINARY_VIV:
        return "GL_SHADER_BINARY_VIV";
    case GL_INT8_NV:
        return "GL_INT8_NV";
    case GL_INT8_VEC2_NV:
        return "GL_INT8_VEC2_NV";
    case GL_INT8_VEC3_NV:
        return "GL_INT8_VEC3_NV";
    case GL_INT8_VEC4_NV:
        return "GL_INT8_VEC4_NV";
    case GL_INT16_NV:
        return "GL_INT16_NV";
    case GL_INT16_VEC2_NV:
        return "GL_INT16_VEC2_NV";
    case GL_INT16_VEC3_NV:
        return "GL_INT16_VEC3_NV";
    case GL_INT16_VEC4_NV:
        return "GL_INT16_VEC4_NV";

    case GL_UNSIGNED_INT8_NV:
        return "GL_UNSIGNED_INT8_NV";
    case GL_UNSIGNED_INT8_VEC2_NV:
        return "GL_UNSIGNED_INT8_VEC2_NV";
    case GL_UNSIGNED_INT8_VEC3_NV:
        return "GL_UNSIGNED_INT8_VEC3_NV";
    case GL_UNSIGNED_INT8_VEC4_NV:
        return "GL_UNSIGNED_INT8_VEC4_NV";
    case GL_UNSIGNED_INT16_NV:
        return "GL_UNSIGNED_INT16_NV";
    case GL_UNSIGNED_INT16_VEC2_NV:
        return "GL_UNSIGNED_INT16_VEC2_NV";
    case GL_UNSIGNED_INT16_VEC3_NV:
        return "GL_UNSIGNED_INT16_VEC3_NV";
    case GL_UNSIGNED_INT16_VEC4_NV:
        return "GL_UNSIGNED_INT16_VEC4_NV";

    case GL_FLOAT16_NV:
        return "GL_FLOAT16_NV";
    case GL_FLOAT16_VEC2_NV:
        return "GL_FLOAT16_VEC2_NV";
    case GL_FLOAT16_VEC3_NV:
        return "GL_FLOAT16_VEC3_NV";
    case GL_FLOAT16_VEC4_NV:
        return "GL_FLOAT16_VEC4_NV";

    case GL_FACTOR_MIN_AMD:
        return "GL_FACTOR_MIN_AMD";
    case GL_FACTOR_MAX_AMD:
        return "GL_FACTOR_MAX_AMD";

    case GL_RGB10_A2UI:
        return "GL_RGB10_A2UI";
    case GL_PATH_FORMAT_SVG_NV:
        return "GL_PATH_FORMAT_SVG_NV";
    case GL_PATH_FORMAT_PS_NV:
        return "GL_PATH_FORMAT_PS_NV";
    case GL_STANDARD_FONT_NAME_NV:
        return "GL_STANDARD_FONT_NAME_NV";
    case GL_SYSTEM_FONT_NAME_NV:
        return "GL_SYSTEM_FONT_NAME_NV";
    case GL_FILE_NAME_NV:
        return "GL_FILE_NAME_NV";
    case GL_PATH_STROKE_WIDTH_NV:
        return "GL_PATH_STROKE_WIDTH_NV";
    case GL_PATH_END_CAPS_NV:
        return "GL_PATH_END_CAPS_NV";
    case GL_PATH_INITIAL_END_CAP_NV:
        return "GL_PATH_INITIAL_END_CAP_NV";
    case GL_PATH_TERMINAL_END_CAP_NV:
        return "GL_PATH_TERMINAL_END_CAP_NV";
    case GL_PATH_JOIN_STYLE_NV:
        return "GL_PATH_JOIN_STYLE_NV";
    case GL_PATH_MITER_LIMIT_NV:
        return "GL_PATH_MITER_LIMIT_NV";
    case GL_PATH_DASH_CAPS_NV:
        return "GL_PATH_DASH_CAPS_NV";
    case GL_PATH_INITIAL_DASH_CAP_NV:
        return "GL_PATH_INITIAL_DASH_CAP_NV";
    case GL_PATH_TERMINAL_DASH_CAP_NV:
        return "GL_PATH_TERMINAL_DASH_CAP_NV";
    case GL_PATH_DASH_OFFSET_NV:
        return "GL_PATH_DASH_OFFSET_NV";
    case GL_PATH_CLIENT_LENGTH_NV:
        return "GL_PATH_CLIENT_LENGTH_NV";
    case GL_PATH_FILL_MODE_NV:
        return "GL_PATH_FILL_MODE_NV";
    case GL_PATH_FILL_MASK_NV:
        return "GL_PATH_FILL_MASK_NV";
    case GL_PATH_FILL_COVER_MODE_NV:
        return "GL_PATH_FILL_COVER_MODE_NV";
    case GL_PATH_STROKE_COVER_MODE_NV:
        return "GL_PATH_STROKE_COVER_MODE_NV";
    case GL_PATH_STROKE_MASK_NV:
        return "GL_PATH_STROKE_MASK_NV";

    case GL_COUNT_UP_NV:
        return "GL_COUNT_UP_NV";
    case GL_COUNT_DOWN_NV:
        return "GL_COUNT_DOWN_NV";
    case GL_PATH_OBJECT_BOUNDING_BOX_NV:
        return "GL_PATH_OBJECT_BOUNDING_BOX_NV";
    case GL_CONVEX_HULL_NV:
        return "GL_CONVEX_HULL_NV";

    case GL_BOUNDING_BOX_NV:
        return "GL_BOUNDING_BOX_NV";
    case GL_TRANSLATE_X_NV:
        return "GL_TRANSLATE_X_NV";
    case GL_TRANSLATE_Y_NV:
        return "GL_TRANSLATE_Y_NV";
    case GL_TRANSLATE_2D_NV:
        return "GL_TRANSLATE_2D_NV";
    case GL_TRANSLATE_3D_NV:
        return "GL_TRANSLATE_3D_NV";
    case GL_AFFINE_2D_NV:
        return "GL_AFFINE_2D_NV";

    case GL_AFFINE_3D_NV:
        return "GL_AFFINE_3D_NV";

    case GL_TRANSPOSE_AFFINE_2D_NV:
        return "GL_TRANSPOSE_AFFINE_2D_NV";

    case GL_TRANSPOSE_AFFINE_3D_NV:
        return "GL_TRANSPOSE_AFFINE_3D_NV";

    case GL_UTF8_NV:
        return "GL_UTF8_NV";
    case GL_UTF16_NV:
        return "GL_UTF16_NV";
    case GL_BOUNDING_BOX_OF_BOUNDING_BOXES_NV:
        return "GL_BOUNDING_BOX_OF_BOUNDING_BOXES_NV";
    case GL_PATH_COMMAND_COUNT_NV:
        return "GL_PATH_COMMAND_COUNT_NV";
    case GL_PATH_COORD_COUNT_NV:
        return "GL_PATH_COORD_COUNT_NV";
    case GL_PATH_DASH_ARRAY_COUNT_NV:
        return "GL_PATH_DASH_ARRAY_COUNT_NV";
    case GL_PATH_COMPUTED_LENGTH_NV:
        return "GL_PATH_COMPUTED_LENGTH_NV";
    case GL_PATH_FILL_BOUNDING_BOX_NV:
        return "GL_PATH_FILL_BOUNDING_BOX_NV";
    case GL_PATH_STROKE_BOUNDING_BOX_NV:
        return "GL_PATH_STROKE_BOUNDING_BOX_NV";
    case GL_SQUARE_NV:
        return "GL_SQUARE_NV";
    case GL_ROUND_NV:
        return "GL_ROUND_NV";
    case GL_TRIANGULAR_NV:
        return "GL_TRIANGULAR_NV";
    case GL_BEVEL_NV:
        return "GL_BEVEL_NV";
    case GL_MITER_REVERT_NV:
        return "GL_MITER_REVERT_NV";
    case GL_MITER_TRUNCATE_NV:
        return "GL_MITER_TRUNCATE_NV";
    case GL_SKIP_MISSING_GLYPH_NV:
        return "GL_SKIP_MISSING_GLYPH_NV";
    case GL_USE_MISSING_GLYPH_NV:
        return "GL_USE_MISSING_GLYPH_NV";
    case GL_PATH_ERROR_POSITION_NV:
        return "GL_PATH_ERROR_POSITION_NV";

    case GL_ACCUM_ADJACENT_PAIRS_NV:
        return "GL_ACCUM_ADJACENT_PAIRS_NV";
    case GL_ADJACENT_PAIRS_NV:
        return "GL_ADJACENT_PAIRS_NV";
    case GL_FIRST_TO_REST_NV:
        return "GL_FIRST_TO_REST_NV";
    case GL_PATH_GEN_MODE_NV:
        return "GL_PATH_GEN_MODE_NV";
    case GL_PATH_GEN_COEFF_NV:
        return "GL_PATH_GEN_COEFF_NV";
    case GL_PATH_GEN_COMPONENTS_NV:
        return "GL_PATH_GEN_COMPONENTS_NV";
    case GL_PATH_DASH_OFFSET_RESET_NV:
        return "GL_PATH_DASH_OFFSET_RESET_NV";
    case GL_MOVE_TO_RESETS_NV:
        return "GL_MOVE_TO_RESETS_NV";
    case GL_MOVE_TO_CONTINUES_NV:
        return "GL_MOVE_TO_CONTINUES_NV";
    case GL_PATH_STENCIL_FUNC_NV:
        return "GL_PATH_STENCIL_FUNC_NV";
    case GL_PATH_STENCIL_REF_NV:
        return "GL_PATH_STENCIL_REF_NV";
    case GL_PATH_STENCIL_VALUE_MASK_NV:
        return "GL_PATH_STENCIL_VALUE_MASK_NV";

    case GL_PATH_STENCIL_DEPTH_OFFSET_FACTOR_NV:
        return "GL_PATH_STENCIL_DEPTH_OFFSET_FACTOR_NV";
    case GL_PATH_STENCIL_DEPTH_OFFSET_UNITS_NV:
        return "GL_PATH_STENCIL_DEPTH_OFFSET_UNITS_NV";
    case GL_PATH_COVER_DEPTH_FUNC_NV:
        return "GL_PATH_COVER_DEPTH_FUNC_NV";

    case GL_COLOR_ATTACHMENT_EXT:
        return "GL_COLOR_ATTACHMENT_EXT";
    case GL_MULTIVIEW_EXT:
        return "GL_MULTIVIEW_EXT";
    case GL_MAX_MULTIVIEW_BUFFERS_EXT:
        return "GL_MAX_MULTIVIEW_BUFFERS_EXT";

    case GL_TEXTURE_2D_MULTISAMPLE:
        return "GL_TEXTURE_2D_MULTISAMPLE";
    case GL_TEXTURE_2D_MULTISAMPLE_ARRAY:
        return "GL_TEXTURE_2D_MULTISAMPLE_ARRAY";

    case GL_MAX_SERVER_WAIT_TIMEOUT:
        return "GL_MAX_SERVER_WAIT_TIMEOUT";
    case GL_OBJECT_TYPE:
        return "GL_OBJECT_TYPE";
    case GL_SYNC_CONDITION:
        return "GL_SYNC_CONDITION";
    case GL_SYNC_STATUS:
        return "GL_SYNC_STATUS";
    case GL_SYNC_FLAGS:
        return "GL_SYNC_FLAGS";
    case GL_SYNC_FENCE:
        return "GL_SYNC_FENCE";
    case GL_SYNC_GPU_COMMANDS_COMPLETE:
        return "GL_SYNC_GPU_COMMANDS_COMPLETE";
    case GL_UNSIGNALED:
        return "GL_UNSIGNALED";
    case GL_SIGNALED:
        return "GL_SIGNALED";
    case GL_ALREADY_SIGNALED:
        return "GL_ALREADY_SIGNALED";
    case GL_TIMEOUT_EXPIRED:
        return "GL_TIMEOUT_EXPIRED";
    case GL_CONDITION_SATISFIED:
        return "GL_CONDITION_SATISFIED";
    case GL_WAIT_FAILED:
        return "GL_WAIT_FAILED";
    case GL_BUFFER_ACCESS_FLAGS:
        return "GL_BUFFER_ACCESS_FLAGS";
    case GL_BUFFER_MAP_LENGTH:
        return "GL_BUFFER_MAP_LENGTH";
    case GL_BUFFER_MAP_OFFSET:
        return "GL_BUFFER_MAP_OFFSET";
    case GL_MAX_VERTEX_OUTPUT_COMPONENTS:
        return "GL_MAX_VERTEX_OUTPUT_COMPONENTS";

    case GL_MAX_FRAGMENT_INPUT_COMPONENTS:
        return "GL_MAX_FRAGMENT_INPUT_COMPONENTS";

    case GL_TEXTURE_IMMUTABLE_FORMAT:
        return "GL_TEXTURE_IMMUTABLE_FORMAT";
    case GL_SGX_PROGRAM_BINARY_IMG:
        return "GL_SGX_PROGRAM_BINARY_IMG";
    case GL_RENDERBUFFER_SAMPLES_IMG:
        return "GL_RENDERBUFFER_SAMPLES_IMG";
    case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_IMG:
        return "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_IMG";
    case GL_MAX_SAMPLES_IMG:
        return "GL_MAX_SAMPLES_IMG";
    case GL_TEXTURE_SAMPLES_IMG:
        return "GL_TEXTURE_SAMPLES_IMG";
    case GL_COMPRESSED_RGBA_PVRTC_2BPPV2_IMG:
        return "GL_COMPRESSED_RGBA_PVRTC_2BPPV2_IMG";
    case GL_COMPRESSED_RGBA_PVRTC_4BPPV2_IMG:
        return "GL_COMPRESSED_RGBA_PVRTC_4BPPV2_IMG";
    case GL_CUBIC_IMG:
        return "GL_CUBIC_IMG";
    case GL_CUBIC_MIPMAP_NEAREST_IMG:
        return "GL_CUBIC_MIPMAP_NEAREST_IMG";
    case GL_CUBIC_MIPMAP_LINEAR_IMG:
        return "GL_CUBIC_MIPMAP_LINEAR_IMG";
    case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_AND_DOWNSAMPLE_IMG:
        return "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_AND_DOWNSAMPLE_IMG";
    case GL_NUM_DOWNSAMPLE_SCALES_IMG:
        return "GL_NUM_DOWNSAMPLE_SCALES_IMG";
    case GL_DOWNSAMPLE_SCALES_IMG:
        return "GL_DOWNSAMPLE_SCALES_IMG";
    case GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_SCALE_IMG:
        return "GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_SCALE_IMG";

    case GL_BUFFER_OBJECT_EXT:
        return "GL_BUFFER_OBJECT_EXT";
    case GL_QUERY_OBJECT_EXT:
        return "GL_QUERY_OBJECT_EXT";
    case GL_VERTEX_ARRAY_OBJECT_EXT:
        return "GL_VERTEX_ARRAY_OBJECT_EXT";

    case GL_SHADER_BINARY_DMP:
        return "GL_SHADER_BINARY_DMP";
    case GL_SMAPHS30_PROGRAM_BINARY_DMP:
        return "GL_SMAPHS30_PROGRAM_BINARY_DMP";
    case GL_SMAPHS_PROGRAM_BINARY_DMP:
        return "GL_SMAPHS_PROGRAM_BINARY_DMP";
    case GL_DMP_PROGRAM_BINARY_DMP:
        return "GL_DMP_PROGRAM_BINARY_DMP";
    case GL_COMPRESSED_R11_EAC:
        return "GL_COMPRESSED_R11_EAC";
    case GL_COMPRESSED_SIGNED_R11_EAC:
        return "GL_COMPRESSED_SIGNED_R11_EAC";
    case GL_COMPRESSED_RG11_EAC:
        return "GL_COMPRESSED_RG11_EAC";
    case GL_COMPRESSED_SIGNED_RG11_EAC:
        return "GL_COMPRESSED_SIGNED_RG11_EAC";
    case GL_COMPRESSED_RGB8_ETC2:
        return "GL_COMPRESSED_RGB8_ETC2";
    case GL_COMPRESSED_SRGB8_ETC2:
        return "GL_COMPRESSED_SRGB8_ETC2";
    case GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2:
        return "GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2";
    case GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2:
        return "GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2";
    case GL_COMPRESSED_RGBA8_ETC2_EAC:
        return "GL_COMPRESSED_RGBA8_ETC2_EAC";
    case GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC:
        return "GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC";
    case GL_BLEND_PREMULTIPLIED_SRC_NV:
        return "GL_BLEND_PREMULTIPLIED_SRC_NV";
    case GL_BLEND_OVERLAP_NV:
        return "GL_BLEND_OVERLAP_NV";
    case GL_UNCORRELATED_NV:
        return "GL_UNCORRELATED_NV";
    case GL_DISJOINT_NV:
        return "GL_DISJOINT_NV";
    case GL_CONJOINT_NV:
        return "GL_CONJOINT_NV";
    case GL_BLEND_ADVANCED_COHERENT_KHR:
        return "GL_BLEND_ADVANCED_COHERENT_KHR";
    case GL_SRC_NV:
        return "GL_SRC_NV";
    case GL_DST_NV:
        return "GL_DST_NV";
    case GL_SRC_OVER_NV:
        return "GL_SRC_OVER_NV";
    case GL_DST_OVER_NV:
        return "GL_DST_OVER_NV";
    case GL_SRC_IN_NV:
        return "GL_SRC_IN_NV";
    case GL_DST_IN_NV:
        return "GL_DST_IN_NV";
    case GL_SRC_OUT_NV:
        return "GL_SRC_OUT_NV";
    case GL_DST_OUT_NV:
        return "GL_DST_OUT_NV";
    case GL_SRC_ATOP_NV:
        return "GL_SRC_ATOP_NV";
    case GL_DST_ATOP_NV:
        return "GL_DST_ATOP_NV";
    case GL_PLUS_NV:
        return "GL_PLUS_NV";
    case GL_PLUS_DARKER_NV:
        return "GL_PLUS_DARKER_NV";
    case GL_MULTIPLY_KHR:
        return "GL_MULTIPLY_KHR";
    case GL_SCREEN_KHR:
        return "GL_SCREEN_KHR";
    case GL_OVERLAY_KHR:
        return "GL_OVERLAY_KHR";
    case GL_DARKEN_KHR:
        return "GL_DARKEN_KHR";
    case GL_LIGHTEN_KHR:
        return "GL_LIGHTEN_KHR";
    case GL_COLORDODGE_KHR:
        return "GL_COLORDODGE_KHR";
    case GL_COLORBURN_KHR:
        return "GL_COLORBURN_KHR";
    case GL_HARDLIGHT_KHR:
        return "GL_HARDLIGHT_KHR";
    case GL_SOFTLIGHT_KHR:
        return "GL_SOFTLIGHT_KHR";
    case GL_DIFFERENCE_KHR:
        return "GL_DIFFERENCE_KHR";
    case GL_MINUS_NV:
        return "GL_MINUS_NV";
    case GL_EXCLUSION_KHR:
        return "GL_EXCLUSION_KHR";
    case GL_CONTRAST_NV:
        return "GL_CONTRAST_NV";
    case GL_INVERT_RGB_NV:
        return "GL_INVERT_RGB_NV";
    case GL_LINEARDODGE_NV:
        return "GL_LINEARDODGE_NV";
    case GL_LINEARBURN_NV:
        return "GL_LINEARBURN_NV";
    case GL_VIVIDLIGHT_NV:
        return "GL_VIVIDLIGHT_NV";
    case GL_LINEARLIGHT_NV:
        return "GL_LINEARLIGHT_NV";
    case GL_PINLIGHT_NV:
        return "GL_PINLIGHT_NV";
    case GL_HARDMIX_NV:
        return "GL_HARDMIX_NV";
    case GL_HSL_HUE_KHR:
        return "GL_HSL_HUE_KHR";
    case GL_HSL_SATURATION_KHR:
        return "GL_HSL_SATURATION_KHR";
    case GL_HSL_COLOR_KHR:
        return "GL_HSL_COLOR_KHR";
    case GL_HSL_LUMINOSITY_KHR:
        return "GL_HSL_LUMINOSITY_KHR";
    case GL_PLUS_CLAMPED_NV:
        return "GL_PLUS_CLAMPED_NV";
    case GL_PLUS_CLAMPED_ALPHA_NV:
        return "GL_PLUS_CLAMPED_ALPHA_NV";
    case GL_MINUS_CLAMPED_NV:
        return "GL_MINUS_CLAMPED_NV";
    case GL_INVERT_OVG_NV:
        return "GL_INVERT_OVG_NV";
    case GL_PRIMITIVE_BOUNDING_BOX_EXT:
        return "GL_PRIMITIVE_BOUNDING_BOX_EXT";

    case GL_FRAGMENT_COVERAGE_TO_COLOR_NV:
        return "GL_FRAGMENT_COVERAGE_TO_COLOR_NV";
    case GL_FRAGMENT_COVERAGE_COLOR_NV:
        return "GL_FRAGMENT_COVERAGE_COLOR_NV";

    case GL_RASTER_MULTISAMPLE_EXT:
        return "GL_RASTER_MULTISAMPLE_EXT";
    case GL_RASTER_SAMPLES_EXT:
        return "GL_RASTER_SAMPLES_EXT";
    case GL_MAX_RASTER_SAMPLES_EXT:
        return "GL_MAX_RASTER_SAMPLES_EXT";
    case GL_RASTER_FIXED_SAMPLE_LOCATIONS_EXT:
        return "GL_RASTER_FIXED_SAMPLE_LOCATIONS_EXT";
    case GL_MULTISAMPLE_RASTERIZATION_ALLOWED_EXT:
        return "GL_MULTISAMPLE_RASTERIZATION_ALLOWED_EXT";
    case GL_EFFECTIVE_RASTER_SAMPLES_EXT:
        return "GL_EFFECTIVE_RASTER_SAMPLES_EXT";
    case GL_DEPTH_SAMPLES_NV:
        return "GL_DEPTH_SAMPLES_NV";
    case GL_STENCIL_SAMPLES_NV:
        return "GL_STENCIL_SAMPLES_NV";
    case GL_MIXED_DEPTH_SAMPLES_SUPPORTED_NV:
        return "GL_MIXED_DEPTH_SAMPLES_SUPPORTED_NV";
    case GL_MIXED_STENCIL_SAMPLES_SUPPORTED_NV:
        return "GL_MIXED_STENCIL_SAMPLES_SUPPORTED_NV";
    case GL_COVERAGE_MODULATION_TABLE_NV:
        return "GL_COVERAGE_MODULATION_TABLE_NV";
    case GL_COVERAGE_MODULATION_NV:
        return "GL_COVERAGE_MODULATION_NV";
    case GL_COVERAGE_MODULATION_TABLE_SIZE_NV:
        return "GL_COVERAGE_MODULATION_TABLE_SIZE_NV";
    case GL_FILL_RECTANGLE_NV:
        return "GL_FILL_RECTANGLE_NV";

    case GL_CONSERVATIVE_RASTERIZATION_NV:
        return "GL_CONSERVATIVE_RASTERIZATION_NV";
    case GL_SUBPIXEL_PRECISION_BIAS_X_BITS_NV:
        return "GL_SUBPIXEL_PRECISION_BIAS_X_BITS_NV";
    case GL_SUBPIXEL_PRECISION_BIAS_Y_BITS_NV:
        return "GL_SUBPIXEL_PRECISION_BIAS_Y_BITS_NV";
    case GL_MAX_SUBPIXEL_PRECISION_BIAS_BITS_NV:
        return "GL_MAX_SUBPIXEL_PRECISION_BIAS_BITS_NV";

    case GL_FONT_GLYPHS_AVAILABLE_NV:
        return "GL_FONT_GLYPHS_AVAILABLE_NV";
    case GL_FONT_TARGET_UNAVAILABLE_NV:
        return "GL_FONT_TARGET_UNAVAILABLE_NV";
    case GL_FONT_UNAVAILABLE_NV:
        return "GL_FONT_UNAVAILABLE_NV";
    case GL_FONT_UNINTELLIGIBLE_NV:
        return "GL_FONT_UNINTELLIGIBLE_NV";
    case GL_STANDARD_FONT_FORMAT_NV:
        return "GL_STANDARD_FONT_FORMAT_NV";
    case GL_FRAGMENT_INPUT_NV:
        return "GL_FRAGMENT_INPUT_NV";

    case GL_MULTISAMPLES_NV:
        return "GL_MULTISAMPLES_NV";
    case GL_SUPERSAMPLE_SCALE_X_NV:
        return "GL_SUPERSAMPLE_SCALE_X_NV";
    case GL_SUPERSAMPLE_SCALE_Y_NV:
        return "GL_SUPERSAMPLE_SCALE_Y_NV";
    case GL_CONFORMANT_NV:
        return "GL_CONFORMANT_NV";

    case GL_NUM_SAMPLE_COUNTS:
        return "GL_NUM_SAMPLE_COUNTS";
    case GL_TRANSLATED_SHADER_SOURCE_LENGTH_ANGLE:
        return "GL_TRANSLATED_SHADER_SOURCE_LENGTH_ANGLE";
    case GL_BGRA8_EXT:
        return "GL_BGRA8_EXT";
    case GL_TEXTURE_USAGE_ANGLE:
        return "GL_TEXTURE_USAGE_ANGLE";
    case GL_FRAMEBUFFER_ATTACHMENT_ANGLE:
        return "GL_FRAMEBUFFER_ATTACHMENT_ANGLE";
    case GL_PACK_REVERSE_ROW_ORDER_ANGLE:
        return "GL_PACK_REVERSE_ROW_ORDER_ANGLE";
    case GL_PROGRAM_BINARY_ANGLE:
        return "GL_PROGRAM_BINARY_ANGLE";
    case GL_COMPRESSED_RGBA_ASTC_4x4_KHR:
        return "GL_COMPRESSED_RGBA_ASTC_4x4_KHR";
    case GL_COMPRESSED_RGBA_ASTC_5x4_KHR:
        return "GL_COMPRESSED_RGBA_ASTC_5x4_KHR";
    case GL_COMPRESSED_RGBA_ASTC_5x5_KHR:
        return "GL_COMPRESSED_RGBA_ASTC_5x5_KHR";
    case GL_COMPRESSED_RGBA_ASTC_6x5_KHR:
        return "GL_COMPRESSED_RGBA_ASTC_6x5_KHR";
    case GL_COMPRESSED_RGBA_ASTC_6x6_KHR:
        return "GL_COMPRESSED_RGBA_ASTC_6x6_KHR";
    case GL_COMPRESSED_RGBA_ASTC_8x5_KHR:
        return "GL_COMPRESSED_RGBA_ASTC_8x5_KHR";
    case GL_COMPRESSED_RGBA_ASTC_8x6_KHR:
        return "GL_COMPRESSED_RGBA_ASTC_8x6_KHR";
    case GL_COMPRESSED_RGBA_ASTC_8x8_KHR:
        return "GL_COMPRESSED_RGBA_ASTC_8x8_KHR";
    case GL_COMPRESSED_RGBA_ASTC_10x5_KHR:
        return "GL_COMPRESSED_RGBA_ASTC_10x5_KHR";
    case GL_COMPRESSED_RGBA_ASTC_10x6_KHR:
        return "GL_COMPRESSED_RGBA_ASTC_10x6_KHR";
    case GL_COMPRESSED_RGBA_ASTC_10x8_KHR:
        return "GL_COMPRESSED_RGBA_ASTC_10x8_KHR";
    case GL_COMPRESSED_RGBA_ASTC_10x10_KHR:
        return "GL_COMPRESSED_RGBA_ASTC_10x10_KHR";
    case GL_COMPRESSED_RGBA_ASTC_12x10_KHR:
        return "GL_COMPRESSED_RGBA_ASTC_12x10_KHR";
    case GL_COMPRESSED_RGBA_ASTC_12x12_KHR:
        return "GL_COMPRESSED_RGBA_ASTC_12x12_KHR";
    case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR:
        return "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR";
    case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4_KHR:
        return "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4_KHR";
    case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5_KHR:
        return "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5_KHR";
    case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5_KHR:
        return "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5_KHR";
    case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6_KHR:
        return "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6_KHR";
    case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5_KHR:
        return "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5_KHR";
    case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6_KHR:
        return "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6_KHR";
    case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8_KHR:
        return "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8_KHR";
    case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5_KHR:
        return "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5_KHR";
    case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6_KHR:
        return "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6_KHR";
    case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8_KHR:
        return "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8_KHR";
    case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10_KHR:
        return "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10_KHR";
    case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10_KHR:
        return "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10_KHR";
    case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12_KHR:
        return "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12_KHR";
    case GL_COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV2_IMG:
        return "GL_COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV2_IMG";
    case GL_COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV2_IMG:
        return "GL_COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV2_IMG";
    case GL_PERFQUERY_COUNTER_EVENT_INTEL:
        return "GL_PERFQUERY_COUNTER_EVENT_INTEL";
    case GL_PERFQUERY_COUNTER_DURATION_NORM_INTEL:
        return "GL_PERFQUERY_COUNTER_DURATION_NORM_INTEL";
    case GL_PERFQUERY_COUNTER_DURATION_RAW_INTEL:
        return "GL_PERFQUERY_COUNTER_DURATION_RAW_INTEL";
    case GL_PERFQUERY_COUNTER_THROUGHPUT_INTEL:
        return "GL_PERFQUERY_COUNTER_THROUGHPUT_INTEL";
    case GL_PERFQUERY_COUNTER_RAW_INTEL:
        return "GL_PERFQUERY_COUNTER_RAW_INTEL";
    case GL_PERFQUERY_COUNTER_TIMESTAMP_INTEL:
        return "GL_PERFQUERY_COUNTER_TIMESTAMP_INTEL";
    case GL_PERFQUERY_COUNTER_DATA_UINT32_INTEL:
        return "GL_PERFQUERY_COUNTER_DATA_UINT32_INTEL";
    case GL_PERFQUERY_COUNTER_DATA_UINT64_INTEL:
        return "GL_PERFQUERY_COUNTER_DATA_UINT64_INTEL";
    case GL_PERFQUERY_COUNTER_DATA_FLOAT_INTEL:
        return "GL_PERFQUERY_COUNTER_DATA_FLOAT_INTEL";
    case GL_PERFQUERY_COUNTER_DATA_DOUBLE_INTEL:
        return "GL_PERFQUERY_COUNTER_DATA_DOUBLE_INTEL";
    case GL_PERFQUERY_COUNTER_DATA_BOOL32_INTEL:
        return "GL_PERFQUERY_COUNTER_DATA_BOOL32_INTEL";
    case GL_PERFQUERY_QUERY_NAME_LENGTH_MAX_INTEL:
        return "GL_PERFQUERY_QUERY_NAME_LENGTH_MAX_INTEL";
    case GL_PERFQUERY_COUNTER_NAME_LENGTH_MAX_INTEL:
        return "GL_PERFQUERY_COUNTER_NAME_LENGTH_MAX_INTEL";
    case GL_PERFQUERY_COUNTER_DESC_LENGTH_MAX_INTEL:
        return "GL_PERFQUERY_COUNTER_DESC_LENGTH_MAX_INTEL";
    case GL_PERFQUERY_GPA_EXTENDED_COUNTERS_INTEL:
        return "GL_PERFQUERY_GPA_EXTENDED_COUNTERS_INTEL";
    case GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_NUM_VIEWS_OVR:
        return "GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_NUM_VIEWS_OVR";
    case GL_MAX_VIEWS_OVR:
        return "GL_MAX_VIEWS_OVR";
    case GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_BASE_VIEW_INDEX_OVR:
        return "GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_BASE_VIEW_INDEX_OVR";
    case GL_MAX_SHADER_COMBINED_LOCAL_STORAGE_FAST_SIZE_EXT:
        return "GL_MAX_SHADER_COMBINED_LOCAL_STORAGE_FAST_SIZE_EXT";
    case GL_MAX_SHADER_COMBINED_LOCAL_STORAGE_SIZE_EXT:
        return "GL_MAX_SHADER_COMBINED_LOCAL_STORAGE_SIZE_EXT";
    case GL_FRAMEBUFFER_INCOMPLETE_INSUFFICIENT_SHADER_COMBINED_LOCAL_STORAGE_EXT:
        return "GL_FRAMEBUFFER_INCOMPLETE_INSUFFICIENT_SHADER_COMBINED_LOCAL_STORAGE_EXT";

    case GL_INVALID_INDEX:
        return "GL_INVALID_INDEX";
    default:
        return NULL;
    }
}

static void
dumpTextureTargetParameters(StateWriter &writer, Context &context, GLenum target, GLuint texture)
{
    (void)context;
    (void)texture;
    writer.beginMember(enumToString(target));
    writer.beginObject();
    //dumpObjectLabel(writer, context, GL_TEXTURE, texture, "GL_TEXTURE_LABEL");
    if (true /*target != GL_TEXTURE_BUFFER*/) {
        // GL_TEXTURE_MAG_FILTER
        {
            flushErrors();
    GLint texture_mag_filter_arr[2] = {0, (GLint)0xdeadc0de};
    glGetTexParameteriv(target, GL_TEXTURE_MAG_FILTER, texture_mag_filter_arr);
    GLint texture_mag_filter = texture_mag_filter_arr[0];
    assert(texture_mag_filter_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_TEXTURE_MAG_FILTER");
    dumpEnum(writer, texture_mag_filter);
                writer.endMember();
            }
        }

        // GL_TEXTURE_MIN_FILTER
        {
            flushErrors();
    GLint texture_min_filter_arr[2] = {0, (GLint)0xdeadc0de};
    glGetTexParameteriv(target, GL_TEXTURE_MIN_FILTER, texture_min_filter_arr);
    GLint texture_min_filter = texture_min_filter_arr[0];
    assert(texture_min_filter_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_TEXTURE_MIN_FILTER");
    dumpEnum(writer, texture_min_filter);
                writer.endMember();
            }
        }

        // GL_TEXTURE_WRAP_S
        {
            flushErrors();
    GLint texture_wrap_s_arr[2] = {0, (GLint)0xdeadc0de};
    glGetTexParameteriv(target, GL_TEXTURE_WRAP_S, texture_wrap_s_arr);
    GLint texture_wrap_s = texture_wrap_s_arr[0];
    assert(texture_wrap_s_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_TEXTURE_WRAP_S");
    dumpEnum(writer, texture_wrap_s);
                writer.endMember();
            }
        }

        // GL_TEXTURE_WRAP_T
        {
            flushErrors();
    GLint texture_wrap_t_arr[2] = {0, (GLint)0xdeadc0de};
    glGetTexParameteriv(target, GL_TEXTURE_WRAP_T, texture_wrap_t_arr);
    GLint texture_wrap_t = texture_wrap_t_arr[0];
    assert(texture_wrap_t_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_TEXTURE_WRAP_T");
    dumpEnum(writer, texture_wrap_t);
                writer.endMember();
            }
        }

        // GL_TEXTURE_WRAP_R
        {
            flushErrors();
    GLint texture_wrap_r_arr[2] = {0, (GLint)0xdeadc0de};
    glGetTexParameteriv(target, GL_TEXTURE_WRAP_R, texture_wrap_r_arr);
    GLint texture_wrap_r = texture_wrap_r_arr[0];
    assert(texture_wrap_r_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_TEXTURE_WRAP_R");
    dumpEnum(writer, texture_wrap_r);
                writer.endMember();
            }
        }


        // GL_TEXTURE_MIN_LOD
        {
            flushErrors();
    GLfloat texture_min_lod_arr[2] = {0, (GLfloat)0xdeadc0de};
    glGetTexParameterfv(target, GL_TEXTURE_MIN_LOD, texture_min_lod_arr);
    GLfloat texture_min_lod = texture_min_lod_arr[0];
    assert(texture_min_lod_arr[1] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_TEXTURE_MIN_LOD");
    writer.writeFloat(texture_min_lod);
                writer.endMember();
            }
        }

        // GL_TEXTURE_MAX_LOD
        {
            flushErrors();
    GLfloat texture_max_lod_arr[2] = {0, (GLfloat)0xdeadc0de};
    glGetTexParameterfv(target, GL_TEXTURE_MAX_LOD, texture_max_lod_arr);
    GLfloat texture_max_lod = texture_max_lod_arr[0];
    assert(texture_max_lod_arr[1] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_TEXTURE_MAX_LOD");
    writer.writeFloat(texture_max_lod);
                writer.endMember();
            }
        }

        // GL_TEXTURE_BASE_LEVEL
        {
            flushErrors();
    GLfloat texture_base_level_arr[2] = {0, (GLfloat)0xdeadc0de};
    glGetTexParameterfv(target, GL_TEXTURE_BASE_LEVEL, texture_base_level_arr);
    GLfloat texture_base_level = texture_base_level_arr[0];
    assert(texture_base_level_arr[1] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_TEXTURE_BASE_LEVEL");
    writer.writeFloat(texture_base_level);
                writer.endMember();
            }
        }

        // GL_TEXTURE_MAX_LEVEL
        {
            flushErrors();
    GLfloat texture_max_level_arr[2] = {0, (GLfloat)0xdeadc0de};
    glGetTexParameterfv(target, GL_TEXTURE_MAX_LEVEL, texture_max_level_arr);
    GLfloat texture_max_level = texture_max_level_arr[0];
    assert(texture_max_level_arr[1] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_TEXTURE_MAX_LEVEL");
    writer.writeFloat(texture_max_level);
                writer.endMember();
            }
        }

        // GL_TEXTURE_IMMUTABLE_LEVELS
        {
            flushErrors();
    GLint texture_immutable_levels_arr[2] = {0, (GLint)0xdeadc0de};
    glGetTexParameteriv(target, GL_TEXTURE_IMMUTABLE_LEVELS, texture_immutable_levels_arr);
    GLint texture_immutable_levels = texture_immutable_levels_arr[0];
    assert(texture_immutable_levels_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_TEXTURE_IMMUTABLE_LEVELS");
    writer.writeInt(texture_immutable_levels);
                writer.endMember();
            }
        }

        // GL_TEXTURE_MAX_ANISOTROPY_EXT
        {
            flushErrors();
    GLfloat texture_max_anisotropy_ext_arr[2] = {0, (GLfloat)0xdeadc0de};
    glGetTexParameterfv(target, GL_TEXTURE_MAX_ANISOTROPY_EXT, texture_max_anisotropy_ext_arr);
    GLfloat texture_max_anisotropy_ext = texture_max_anisotropy_ext_arr[0];
    assert(texture_max_anisotropy_ext_arr[1] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_TEXTURE_MAX_ANISOTROPY_EXT");
    writer.writeFloat(texture_max_anisotropy_ext);
                writer.endMember();
            }
        }

        // GL_TEXTURE_COMPARE_MODE
        {
            flushErrors();
    GLint texture_compare_mode_arr[2] = {0, (GLint)0xdeadc0de};
    glGetTexParameteriv(target, GL_TEXTURE_COMPARE_MODE, texture_compare_mode_arr);
    GLint texture_compare_mode = texture_compare_mode_arr[0];
    assert(texture_compare_mode_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_TEXTURE_COMPARE_MODE");
    dumpEnum(writer, texture_compare_mode);
                writer.endMember();
            }
        }

        // GL_TEXTURE_COMPARE_FUNC
        {
            flushErrors();
    GLint texture_compare_func_arr[2] = {0, (GLint)0xdeadc0de};
    glGetTexParameteriv(target, GL_TEXTURE_COMPARE_FUNC, texture_compare_func_arr);
    GLint texture_compare_func = texture_compare_func_arr[0];
    assert(texture_compare_func_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_TEXTURE_COMPARE_FUNC");
    dumpEnum(writer, texture_compare_func);
                writer.endMember();
            }
        }

        // GL_TEXTURE_SRGB_DECODE_EXT
        {
            flushErrors();
    GLint texture_srgb_decode_ext_arr[2] = {0, (GLint)0xdeadc0de};
    glGetTexParameteriv(target, GL_TEXTURE_SRGB_DECODE_EXT, texture_srgb_decode_ext_arr);
    GLint texture_srgb_decode_ext = texture_srgb_decode_ext_arr[0];
    assert(texture_srgb_decode_ext_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_TEXTURE_SRGB_DECODE_EXT");
    dumpEnum(writer, texture_srgb_decode_ext);
                writer.endMember();
            }
        }

        // GL_TEXTURE_SWIZZLE_R
        {
            flushErrors();
    GLint texture_swizzle_r_arr[2] = {0, (GLint)0xdeadc0de};
    glGetTexParameteriv(target, GL_TEXTURE_SWIZZLE_R, texture_swizzle_r_arr);
    GLint texture_swizzle_r = texture_swizzle_r_arr[0];
    assert(texture_swizzle_r_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_TEXTURE_SWIZZLE_R");
    dumpEnum(writer, texture_swizzle_r);
                writer.endMember();
            }
        }

        // GL_TEXTURE_SWIZZLE_G
        {
            flushErrors();
    GLint texture_swizzle_g_arr[2] = {0, (GLint)0xdeadc0de};
    glGetTexParameteriv(target, GL_TEXTURE_SWIZZLE_G, texture_swizzle_g_arr);
    GLint texture_swizzle_g = texture_swizzle_g_arr[0];
    assert(texture_swizzle_g_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_TEXTURE_SWIZZLE_G");
    dumpEnum(writer, texture_swizzle_g);
                writer.endMember();
            }
        }

        // GL_TEXTURE_SWIZZLE_B
        {
            flushErrors();
    GLint texture_swizzle_b_arr[2] = {0, (GLint)0xdeadc0de};
    glGetTexParameteriv(target, GL_TEXTURE_SWIZZLE_B, texture_swizzle_b_arr);
    GLint texture_swizzle_b = texture_swizzle_b_arr[0];
    assert(texture_swizzle_b_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_TEXTURE_SWIZZLE_B");
    dumpEnum(writer, texture_swizzle_b);
                writer.endMember();
            }
        }

        // GL_TEXTURE_SWIZZLE_A
        {
            flushErrors();
    GLint texture_swizzle_a_arr[2] = {0, (GLint)0xdeadc0de};
    glGetTexParameteriv(target, GL_TEXTURE_SWIZZLE_A, texture_swizzle_a_arr);
    GLint texture_swizzle_a = texture_swizzle_a_arr[0];
    assert(texture_swizzle_a_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_TEXTURE_SWIZZLE_A");
    dumpEnum(writer, texture_swizzle_a);
                writer.endMember();
            }
        }

        // GL_TEXTURE_ASTC_DECODE_PRECISION_EXT
        {
            flushErrors();
    GLint texture_astc_decode_precision_ext_arr[2] = {0, (GLint)0xdeadc0de};
    glGetTexParameteriv(target, GL_TEXTURE_ASTC_DECODE_PRECISION_EXT, texture_astc_decode_precision_ext_arr);
    GLint texture_astc_decode_precision_ext = texture_astc_decode_precision_ext_arr[0];
    assert(texture_astc_decode_precision_ext_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_TEXTURE_ASTC_DECODE_PRECISION_EXT");
    dumpEnum(writer, texture_astc_decode_precision_ext);
                writer.endMember();
            }
        }

        // GL_TEXTURE_IMMUTABLE_FORMAT
        {
            flushErrors();
    GLint texture_immutable_format_arr[2] = {0, (GLint)0xdeadc0de};
    glGetTexParameteriv(target, GL_TEXTURE_IMMUTABLE_FORMAT, texture_immutable_format_arr);
    GLint texture_immutable_format = texture_immutable_format_arr[0];
    assert(texture_immutable_format_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_TEXTURE_IMMUTABLE_FORMAT");
    dumpBoolean(writer, texture_immutable_format);
                writer.endMember();
            }
        }


    }
    writer.endObject();
    writer.endMember(); // target
}

static void
dumpFramebufferAttachementParameters(StateWriter &writer, Context &context, GLenum target, GLenum attachment)
{
    (void)context;
            {
                GLint object_type = GL_NONE;
                glGetFramebufferAttachmentParameteriv(target, attachment, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &object_type);
                if (object_type != GL_NONE) {
                    writer.beginMember(enumToString(attachment));
                    writer.beginObject();
        // GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING
        {
            flushErrors();
    GLint framebuffer_attachment_color_encoding_arr[2] = {0, (GLint)0xdeadc0de};
    glGetFramebufferAttachmentParameteriv(target, attachment, GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING, framebuffer_attachment_color_encoding_arr);
    GLint framebuffer_attachment_color_encoding = framebuffer_attachment_color_encoding_arr[0];
    assert(framebuffer_attachment_color_encoding_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING");
    dumpEnum(writer, framebuffer_attachment_color_encoding);
                writer.endMember();
            }
        }

        // GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE
        {
            flushErrors();
    GLint framebuffer_attachment_component_type_arr[2] = {0, (GLint)0xdeadc0de};
    glGetFramebufferAttachmentParameteriv(target, attachment, GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE, framebuffer_attachment_component_type_arr);
    GLint framebuffer_attachment_component_type = framebuffer_attachment_component_type_arr[0];
    assert(framebuffer_attachment_component_type_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE");
    dumpEnum(writer, framebuffer_attachment_component_type);
                writer.endMember();
            }
        }

        // GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE
        {
            flushErrors();
    GLint framebuffer_attachment_red_size_arr[2] = {0, (GLint)0xdeadc0de};
    glGetFramebufferAttachmentParameteriv(target, attachment, GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE, framebuffer_attachment_red_size_arr);
    GLint framebuffer_attachment_red_size = framebuffer_attachment_red_size_arr[0];
    assert(framebuffer_attachment_red_size_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE");
    writer.writeInt(framebuffer_attachment_red_size);
                writer.endMember();
            }
        }

        // GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE
        {
            flushErrors();
    GLint framebuffer_attachment_green_size_arr[2] = {0, (GLint)0xdeadc0de};
    glGetFramebufferAttachmentParameteriv(target, attachment, GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE, framebuffer_attachment_green_size_arr);
    GLint framebuffer_attachment_green_size = framebuffer_attachment_green_size_arr[0];
    assert(framebuffer_attachment_green_size_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE");
    writer.writeInt(framebuffer_attachment_green_size);
                writer.endMember();
            }
        }

        // GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE
        {
            flushErrors();
    GLint framebuffer_attachment_blue_size_arr[2] = {0, (GLint)0xdeadc0de};
    glGetFramebufferAttachmentParameteriv(target, attachment, GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE, framebuffer_attachment_blue_size_arr);
    GLint framebuffer_attachment_blue_size = framebuffer_attachment_blue_size_arr[0];
    assert(framebuffer_attachment_blue_size_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE");
    writer.writeInt(framebuffer_attachment_blue_size);
                writer.endMember();
            }
        }

        // GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE
        {
            flushErrors();
    GLint framebuffer_attachment_alpha_size_arr[2] = {0, (GLint)0xdeadc0de};
    glGetFramebufferAttachmentParameteriv(target, attachment, GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE, framebuffer_attachment_alpha_size_arr);
    GLint framebuffer_attachment_alpha_size = framebuffer_attachment_alpha_size_arr[0];
    assert(framebuffer_attachment_alpha_size_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE");
    writer.writeInt(framebuffer_attachment_alpha_size);
                writer.endMember();
            }
        }

        // GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE
        {
            flushErrors();
    GLint framebuffer_attachment_depth_size_arr[2] = {0, (GLint)0xdeadc0de};
    glGetFramebufferAttachmentParameteriv(target, attachment, GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE, framebuffer_attachment_depth_size_arr);
    GLint framebuffer_attachment_depth_size = framebuffer_attachment_depth_size_arr[0];
    assert(framebuffer_attachment_depth_size_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE");
    writer.writeInt(framebuffer_attachment_depth_size);
                writer.endMember();
            }
        }

        // GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE
        {
            flushErrors();
    GLint framebuffer_attachment_stencil_size_arr[2] = {0, (GLint)0xdeadc0de};
    glGetFramebufferAttachmentParameteriv(target, attachment, GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE, framebuffer_attachment_stencil_size_arr);
    GLint framebuffer_attachment_stencil_size = framebuffer_attachment_stencil_size_arr[0];
    assert(framebuffer_attachment_stencil_size_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE");
    writer.writeInt(framebuffer_attachment_stencil_size);
                writer.endMember();
            }
        }

        // GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE
        {
            flushErrors();
    GLint framebuffer_attachment_object_type_arr[2] = {0, (GLint)0xdeadc0de};
    glGetFramebufferAttachmentParameteriv(target, attachment, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, framebuffer_attachment_object_type_arr);
    GLint framebuffer_attachment_object_type = framebuffer_attachment_object_type_arr[0];
    assert(framebuffer_attachment_object_type_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE");
    dumpEnum(writer, framebuffer_attachment_object_type);
                writer.endMember();
            }
        }

        // GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME
        {
            flushErrors();
    GLint framebuffer_attachment_object_name_arr[2] = {0, (GLint)0xdeadc0de};
    glGetFramebufferAttachmentParameteriv(target, attachment, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, framebuffer_attachment_object_name_arr);
    GLint framebuffer_attachment_object_name = framebuffer_attachment_object_name_arr[0];
    assert(framebuffer_attachment_object_name_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME");
    writer.writeInt(framebuffer_attachment_object_name);
                writer.endMember();
            }
        }

        // GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL
        {
            flushErrors();
    GLint framebuffer_attachment_texture_level_arr[2] = {0, (GLint)0xdeadc0de};
    glGetFramebufferAttachmentParameteriv(target, attachment, GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL, framebuffer_attachment_texture_level_arr);
    GLint framebuffer_attachment_texture_level = framebuffer_attachment_texture_level_arr[0];
    assert(framebuffer_attachment_texture_level_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL");
    writer.writeInt(framebuffer_attachment_texture_level);
                writer.endMember();
            }
        }

        // GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE
        {
            flushErrors();
    GLint framebuffer_attachment_texture_cube_map_face_arr[2] = {0, (GLint)0xdeadc0de};
    glGetFramebufferAttachmentParameteriv(target, attachment, GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE, framebuffer_attachment_texture_cube_map_face_arr);
    GLint framebuffer_attachment_texture_cube_map_face = framebuffer_attachment_texture_cube_map_face_arr[0];
    assert(framebuffer_attachment_texture_cube_map_face_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE");
    dumpEnum(writer, framebuffer_attachment_texture_cube_map_face);
                writer.endMember();
            }
        }

        // GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER
        {
            flushErrors();
    GLint framebuffer_attachment_texture_layer_arr[2] = {0, (GLint)0xdeadc0de};
    glGetFramebufferAttachmentParameteriv(target, attachment, GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER, framebuffer_attachment_texture_layer_arr);
    GLint framebuffer_attachment_texture_layer = framebuffer_attachment_texture_layer_arr[0];
    assert(framebuffer_attachment_texture_layer_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER");
    writer.writeInt(framebuffer_attachment_texture_layer);
                writer.endMember();
            }
        }


                    GLint object_name = 0;
                    glGetFramebufferAttachmentParameteriv(target, attachment, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, &object_name);
                    writer.endObject();
                    writer.endMember(); // GL_x_ATTACHMENT
                }
            }
}

void dumpParameters(StateWriter &writer, Context &context)
{
    ScopedAllocator _allocator;
    (void)_allocator;

    writer.beginMember("parameters");
    writer.beginObject();


        // GL_LINE_WIDTH
        {
            flushErrors();
    GLfloat line_width_arr[2] = {0, (GLfloat)0xdeadc0de};
    glGetFloatv(GL_LINE_WIDTH, line_width_arr);
    GLfloat line_width = line_width_arr[0];
    assert(line_width_arr[1] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_LINE_WIDTH");
    writer.writeFloat(line_width);
                writer.endMember();
            }
        }





        // GL_CULL_FACE
        {
            flushErrors();
    GLboolean cull_face_arr[2] = {0, (GLboolean)0xdeadc0de};
    glGetBooleanv(GL_CULL_FACE, cull_face_arr);
    GLboolean cull_face = cull_face_arr[0];
    assert(cull_face_arr[1] == (GLboolean)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_CULL_FACE");
    dumpBoolean(writer, cull_face);
                writer.endMember();
            }
        }

        // GL_CULL_FACE_MODE
        {
            flushErrors();
    GLint cull_face_mode_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_CULL_FACE_MODE, cull_face_mode_arr);
    GLint cull_face_mode = cull_face_mode_arr[0];
    assert(cull_face_mode_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_CULL_FACE_MODE");
    dumpEnum(writer, cull_face_mode);
                writer.endMember();
            }
        }

        // GL_FRONT_FACE
        {
            flushErrors();
    GLint front_face_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_FRONT_FACE, front_face_arr);
    GLint front_face = front_face_arr[0];
    assert(front_face_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_FRONT_FACE");
    dumpEnum(writer, front_face);
                writer.endMember();
            }
        }

        // GL_DEPTH_RANGE
        {
            flushErrors();
    GLfloat depth_range[2 + 1];
    memset(depth_range, 0, 2 * sizeof *depth_range);
    depth_range[2] = (GLfloat)0xdeadc0de;
    if (2) {
        glGetFloatv(GL_DEPTH_RANGE, depth_range);
    }
    assert(depth_range[2] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_DEPTH_RANGE");
    writer.beginArray();
    for (unsigned _i17 = 0; _i17 < 2; ++_i17) {
    writer.writeFloat(depth_range[_i17]);
    }
    writer.endArray();
                writer.endMember();
            }
        }

        // GL_DEPTH_TEST
        {
            flushErrors();
    GLboolean depth_test_arr[2] = {0, (GLboolean)0xdeadc0de};
    glGetBooleanv(GL_DEPTH_TEST, depth_test_arr);
    GLboolean depth_test = depth_test_arr[0];
    assert(depth_test_arr[1] == (GLboolean)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_DEPTH_TEST");
    dumpBoolean(writer, depth_test);
                writer.endMember();
            }
        }

        // GL_DEPTH_WRITEMASK
        {
            flushErrors();
    GLboolean depth_writemask_arr[2] = {0, (GLboolean)0xdeadc0de};
    glGetBooleanv(GL_DEPTH_WRITEMASK, depth_writemask_arr);
    GLboolean depth_writemask = depth_writemask_arr[0];
    assert(depth_writemask_arr[1] == (GLboolean)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_DEPTH_WRITEMASK");
    dumpBoolean(writer, depth_writemask);
                writer.endMember();
            }
        }

        // GL_DEPTH_CLEAR_VALUE
        {
            flushErrors();
    GLfloat depth_clear_value_arr[2] = {0, (GLfloat)0xdeadc0de};
    glGetFloatv(GL_DEPTH_CLEAR_VALUE, depth_clear_value_arr);
    GLfloat depth_clear_value = depth_clear_value_arr[0];
    assert(depth_clear_value_arr[1] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_DEPTH_CLEAR_VALUE");
    writer.writeFloat(depth_clear_value);
                writer.endMember();
            }
        }

        // GL_DEPTH_FUNC
        {
            flushErrors();
    GLint depth_func_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_DEPTH_FUNC, depth_func_arr);
    GLint depth_func = depth_func_arr[0];
    assert(depth_func_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_DEPTH_FUNC");
    dumpEnum(writer, depth_func);
                writer.endMember();
            }
        }

        // GL_STENCIL_TEST
        {
            flushErrors();
    GLboolean stencil_test_arr[2] = {0, (GLboolean)0xdeadc0de};
    glGetBooleanv(GL_STENCIL_TEST, stencil_test_arr);
    GLboolean stencil_test = stencil_test_arr[0];
    assert(stencil_test_arr[1] == (GLboolean)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_STENCIL_TEST");
    dumpBoolean(writer, stencil_test);
                writer.endMember();
            }
        }

        // GL_STENCIL_CLEAR_VALUE
        {
            flushErrors();
    GLint stencil_clear_value_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_STENCIL_CLEAR_VALUE, stencil_clear_value_arr);
    GLint stencil_clear_value = stencil_clear_value_arr[0];
    assert(stencil_clear_value_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_STENCIL_CLEAR_VALUE");
    writer.writeInt(stencil_clear_value);
                writer.endMember();
            }
        }

        // GL_STENCIL_FUNC
        {
            flushErrors();
    GLint stencil_func_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_STENCIL_FUNC, stencil_func_arr);
    GLint stencil_func = stencil_func_arr[0];
    assert(stencil_func_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_STENCIL_FUNC");
    dumpEnum(writer, stencil_func);
                writer.endMember();
            }
        }

        // GL_STENCIL_VALUE_MASK
        {
            flushErrors();
    GLint stencil_value_mask_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_STENCIL_VALUE_MASK, stencil_value_mask_arr);
    GLint stencil_value_mask = stencil_value_mask_arr[0];
    assert(stencil_value_mask_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_STENCIL_VALUE_MASK");
    writer.writeInt(stencil_value_mask);
                writer.endMember();
            }
        }

        // GL_STENCIL_FAIL
        {
            flushErrors();
    GLint stencil_fail_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_STENCIL_FAIL, stencil_fail_arr);
    GLint stencil_fail = stencil_fail_arr[0];
    assert(stencil_fail_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_STENCIL_FAIL");
    dumpEnum(writer, stencil_fail);
                writer.endMember();
            }
        }

        // GL_STENCIL_PASS_DEPTH_FAIL
        {
            flushErrors();
    GLint stencil_pass_depth_fail_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_STENCIL_PASS_DEPTH_FAIL, stencil_pass_depth_fail_arr);
    GLint stencil_pass_depth_fail = stencil_pass_depth_fail_arr[0];
    assert(stencil_pass_depth_fail_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_STENCIL_PASS_DEPTH_FAIL");
    dumpEnum(writer, stencil_pass_depth_fail);
                writer.endMember();
            }
        }

        // GL_STENCIL_PASS_DEPTH_PASS
        {
            flushErrors();
    GLint stencil_pass_depth_pass_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_STENCIL_PASS_DEPTH_PASS, stencil_pass_depth_pass_arr);
    GLint stencil_pass_depth_pass = stencil_pass_depth_pass_arr[0];
    assert(stencil_pass_depth_pass_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_STENCIL_PASS_DEPTH_PASS");
    dumpEnum(writer, stencil_pass_depth_pass);
                writer.endMember();
            }
        }

        // GL_STENCIL_REF
        {
            flushErrors();
    GLint stencil_ref_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_STENCIL_REF, stencil_ref_arr);
    GLint stencil_ref = stencil_ref_arr[0];
    assert(stencil_ref_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_STENCIL_REF");
    writer.writeInt(stencil_ref);
                writer.endMember();
            }
        }

        // GL_STENCIL_WRITEMASK
        {
            flushErrors();
    GLint stencil_writemask_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_STENCIL_WRITEMASK, stencil_writemask_arr);
    GLint stencil_writemask = stencil_writemask_arr[0];
    assert(stencil_writemask_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_STENCIL_WRITEMASK");
    writer.writeInt(stencil_writemask);
                writer.endMember();
            }
        }



        // GL_VIEWPORT
        {
            flushErrors();
    GLint viewport[4 + 1];
    memset(viewport, 0, 4 * sizeof *viewport);
    viewport[4] = (GLint)0xdeadc0de;
    if (4) {
        glGetIntegerv(GL_VIEWPORT, viewport);
    }
    assert(viewport[4] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_VIEWPORT");
    writer.beginArray();
    for (unsigned _i19 = 0; _i19 < 4; ++_i19) {
    writer.writeInt(viewport[_i19]);
    }
    writer.endArray();
                writer.endMember();
            }
        }



        // GL_DITHER
        {
            flushErrors();
    GLboolean dither_arr[2] = {0, (GLboolean)0xdeadc0de};
    glGetBooleanv(GL_DITHER, dither_arr);
    GLboolean dither = dither_arr[0];
    assert(dither_arr[1] == (GLboolean)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_DITHER");
    dumpBoolean(writer, dither);
                writer.endMember();
            }
        }



        // GL_BLEND
        {
            flushErrors();
    GLboolean blend_arr[2] = {0, (GLboolean)0xdeadc0de};
    glGetBooleanv(GL_BLEND, blend_arr);
    GLboolean blend = blend_arr[0];
    assert(blend_arr[1] == (GLboolean)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BLEND");
    dumpBoolean(writer, blend);
                writer.endMember();
            }
        }



        // GL_READ_BUFFER
        {
            flushErrors();
    GLint read_buffer_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_READ_BUFFER, read_buffer_arr);
    GLint read_buffer = read_buffer_arr[0];
    assert(read_buffer_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_READ_BUFFER");
    dumpEnum(writer, read_buffer);
                writer.endMember();
            }
        }

        // GL_SCISSOR_BOX
        {
            flushErrors();
    GLint scissor_box[4 + 1];
    memset(scissor_box, 0, 4 * sizeof *scissor_box);
    scissor_box[4] = (GLint)0xdeadc0de;
    if (4) {
        glGetIntegerv(GL_SCISSOR_BOX, scissor_box);
    }
    assert(scissor_box[4] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_SCISSOR_BOX");
    writer.beginArray();
    for (unsigned _i23 = 0; _i23 < 4; ++_i23) {
    writer.writeInt(scissor_box[_i23]);
    }
    writer.endArray();
                writer.endMember();
            }
        }

        // GL_SCISSOR_TEST
        {
            flushErrors();
    GLboolean scissor_test_arr[2] = {0, (GLboolean)0xdeadc0de};
    glGetBooleanv(GL_SCISSOR_TEST, scissor_test_arr);
    GLboolean scissor_test = scissor_test_arr[0];
    assert(scissor_test_arr[1] == (GLboolean)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_SCISSOR_TEST");
    dumpBoolean(writer, scissor_test);
                writer.endMember();
            }
        }



        // GL_COLOR_CLEAR_VALUE
        {
            flushErrors();
    GLfloat color_clear_value[4 + 1];
    memset(color_clear_value, 0, 4 * sizeof *color_clear_value);
    color_clear_value[4] = (GLfloat)0xdeadc0de;
    if (4) {
        glGetFloatv(GL_COLOR_CLEAR_VALUE, color_clear_value);
    }
    assert(color_clear_value[4] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_COLOR_CLEAR_VALUE");
    writer.beginArray();
    for (unsigned _i24 = 0; _i24 < 4; ++_i24) {
    writer.writeFloat(color_clear_value[_i24]);
    }
    writer.endArray();
                writer.endMember();
            }
        }

        // GL_COLOR_WRITEMASK
        {
            flushErrors();
    GLboolean color_writemask[4 + 1];
    memset(color_writemask, 0, 4 * sizeof *color_writemask);
    color_writemask[4] = (GLboolean)0xdeadc0de;
    if (4) {
        glGetBooleanv(GL_COLOR_WRITEMASK, color_writemask);
    }
    assert(color_writemask[4] == (GLboolean)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_COLOR_WRITEMASK");
    writer.beginArray();
    for (unsigned _i25 = 0; _i25 < 4; ++_i25) {
    dumpBoolean(writer, color_writemask[_i25]);
    }
    writer.endArray();
                writer.endMember();
            }
        }



        // GL_UNPACK_ROW_LENGTH
        {
            flushErrors();
    GLint unpack_row_length_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_UNPACK_ROW_LENGTH, unpack_row_length_arr);
    GLint unpack_row_length = unpack_row_length_arr[0];
    assert(unpack_row_length_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_UNPACK_ROW_LENGTH");
    writer.writeInt(unpack_row_length);
                writer.endMember();
            }
        }

        // GL_UNPACK_SKIP_ROWS
        {
            flushErrors();
    GLint unpack_skip_rows_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_UNPACK_SKIP_ROWS, unpack_skip_rows_arr);
    GLint unpack_skip_rows = unpack_skip_rows_arr[0];
    assert(unpack_skip_rows_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_UNPACK_SKIP_ROWS");
    writer.writeInt(unpack_skip_rows);
                writer.endMember();
            }
        }

        // GL_UNPACK_SKIP_PIXELS
        {
            flushErrors();
    GLint unpack_skip_pixels_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_UNPACK_SKIP_PIXELS, unpack_skip_pixels_arr);
    GLint unpack_skip_pixels = unpack_skip_pixels_arr[0];
    assert(unpack_skip_pixels_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_UNPACK_SKIP_PIXELS");
    writer.writeInt(unpack_skip_pixels);
                writer.endMember();
            }
        }

        // GL_UNPACK_ALIGNMENT
        {
            flushErrors();
    GLint unpack_alignment_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_UNPACK_ALIGNMENT, unpack_alignment_arr);
    GLint unpack_alignment = unpack_alignment_arr[0];
    assert(unpack_alignment_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_UNPACK_ALIGNMENT");
    writer.writeInt(unpack_alignment);
                writer.endMember();
            }
        }



        // GL_PACK_ROW_LENGTH
        {
            flushErrors();
    GLint pack_row_length_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_PACK_ROW_LENGTH, pack_row_length_arr);
    GLint pack_row_length = pack_row_length_arr[0];
    assert(pack_row_length_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_PACK_ROW_LENGTH");
    writer.writeInt(pack_row_length);
                writer.endMember();
            }
        }

        // GL_PACK_SKIP_ROWS
        {
            flushErrors();
    GLint pack_skip_rows_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_PACK_SKIP_ROWS, pack_skip_rows_arr);
    GLint pack_skip_rows = pack_skip_rows_arr[0];
    assert(pack_skip_rows_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_PACK_SKIP_ROWS");
    writer.writeInt(pack_skip_rows);
                writer.endMember();
            }
        }

        // GL_PACK_SKIP_PIXELS
        {
            flushErrors();
    GLint pack_skip_pixels_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_PACK_SKIP_PIXELS, pack_skip_pixels_arr);
    GLint pack_skip_pixels = pack_skip_pixels_arr[0];
    assert(pack_skip_pixels_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_PACK_SKIP_PIXELS");
    writer.writeInt(pack_skip_pixels);
                writer.endMember();
            }
        }

        // GL_PACK_ALIGNMENT
        {
            flushErrors();
    GLint pack_alignment_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_PACK_ALIGNMENT, pack_alignment_arr);
    GLint pack_alignment = pack_alignment_arr[0];
    assert(pack_alignment_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_PACK_ALIGNMENT");
    writer.writeInt(pack_alignment);
                writer.endMember();
            }
        }



        // GL_MAX_TEXTURE_SIZE
        {
            flushErrors();
    GLint max_texture_size_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, max_texture_size_arr);
    GLint max_texture_size = max_texture_size_arr[0];
    assert(max_texture_size_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_MAX_TEXTURE_SIZE");
    writer.writeInt(max_texture_size);
                writer.endMember();
            }
        }



        // GL_MAX_VIEWPORT_DIMS
        {
            flushErrors();
    GLfloat max_viewport_dims[2 + 1];
    memset(max_viewport_dims, 0, 2 * sizeof *max_viewport_dims);
    max_viewport_dims[2] = (GLfloat)0xdeadc0de;
    if (2) {
        glGetFloatv(GL_MAX_VIEWPORT_DIMS, max_viewport_dims);
    }
    assert(max_viewport_dims[2] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_MAX_VIEWPORT_DIMS");
    writer.beginArray();
    for (unsigned _i26 = 0; _i26 < 2; ++_i26) {
    writer.writeFloat(max_viewport_dims[_i26]);
    }
    writer.endArray();
                writer.endMember();
            }
        }


        // GL_SUBPIXEL_BITS
        {
            flushErrors();
    GLint subpixel_bits_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_SUBPIXEL_BITS, subpixel_bits_arr);
    GLint subpixel_bits = subpixel_bits_arr[0];
    assert(subpixel_bits_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_SUBPIXEL_BITS");
    writer.writeInt(subpixel_bits);
                writer.endMember();
            }
        }



        // GL_RED_BITS
        {
            flushErrors();
    GLint red_bits_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_RED_BITS, red_bits_arr);
    GLint red_bits = red_bits_arr[0];
    assert(red_bits_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_RED_BITS");
    writer.writeInt(red_bits);
                writer.endMember();
            }
        }

        // GL_GREEN_BITS
        {
            flushErrors();
    GLint green_bits_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_GREEN_BITS, green_bits_arr);
    GLint green_bits = green_bits_arr[0];
    assert(green_bits_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_GREEN_BITS");
    writer.writeInt(green_bits);
                writer.endMember();
            }
        }

        // GL_BLUE_BITS
        {
            flushErrors();
    GLint blue_bits_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_BLUE_BITS, blue_bits_arr);
    GLint blue_bits = blue_bits_arr[0];
    assert(blue_bits_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BLUE_BITS");
    writer.writeInt(blue_bits);
                writer.endMember();
            }
        }

        // GL_ALPHA_BITS
        {
            flushErrors();
    GLint alpha_bits_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_ALPHA_BITS, alpha_bits_arr);
    GLint alpha_bits = alpha_bits_arr[0];
    assert(alpha_bits_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_ALPHA_BITS");
    writer.writeInt(alpha_bits);
                writer.endMember();
            }
        }

        // GL_DEPTH_BITS
        {
            flushErrors();
    GLint depth_bits_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_DEPTH_BITS, depth_bits_arr);
    GLint depth_bits = depth_bits_arr[0];
    assert(depth_bits_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_DEPTH_BITS");
    writer.writeInt(depth_bits);
                writer.endMember();
            }
        }

        // GL_STENCIL_BITS
        {
            flushErrors();
    GLint stencil_bits_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_STENCIL_BITS, stencil_bits_arr);
    GLint stencil_bits = stencil_bits_arr[0];
    assert(stencil_bits_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_STENCIL_BITS");
    writer.writeInt(stencil_bits);
                writer.endMember();
            }
        }

        // GL_VENDOR
        {
            flushErrors();
    char * vendor = (char *)glGetString(GL_VENDOR);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_VENDOR");
    writer.writeString((const char *)vendor);
                writer.endMember();
            }
        }

        // GL_RENDERER
        {
            flushErrors();
    char * renderer = (char *)glGetString(GL_RENDERER);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_RENDERER");
    writer.writeString((const char *)renderer);
                writer.endMember();
            }
        }

        // GL_VERSION
        {
            flushErrors();
    char * version = (char *)glGetString(GL_VERSION);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_VERSION");
    writer.writeString((const char *)version);
                writer.endMember();
            }
        }

        // GL_EXTENSIONS
        {
            flushErrors();
    char * extensions = (char *)glGetString(GL_EXTENSIONS);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_EXTENSIONS");
    writer.writeString((const char *)extensions);
                writer.endMember();
            }
        }

        // GL_POLYGON_OFFSET_UNITS
        {
            flushErrors();
    GLfloat polygon_offset_units_arr[2] = {0, (GLfloat)0xdeadc0de};
    glGetFloatv(GL_POLYGON_OFFSET_UNITS, polygon_offset_units_arr);
    GLfloat polygon_offset_units = polygon_offset_units_arr[0];
    assert(polygon_offset_units_arr[1] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_POLYGON_OFFSET_UNITS");
    writer.writeFloat(polygon_offset_units);
                writer.endMember();
            }
        }


        // GL_BLEND_COLOR
        {
            flushErrors();
    GLfloat blend_color[4 + 1];
    memset(blend_color, 0, 4 * sizeof *blend_color);
    blend_color[4] = (GLfloat)0xdeadc0de;
    if (4) {
        glGetFloatv(GL_BLEND_COLOR, blend_color);
    }
    assert(blend_color[4] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BLEND_COLOR");
    writer.beginArray();
    for (unsigned _i30 = 0; _i30 < 4; ++_i30) {
    writer.writeFloat(blend_color[_i30]);
    }
    writer.endArray();
                writer.endMember();
            }
        }

        // GL_BLEND_EQUATION
        {
            flushErrors();
    GLint blend_equation_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_BLEND_EQUATION, blend_equation_arr);
    GLint blend_equation = blend_equation_arr[0];
    assert(blend_equation_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BLEND_EQUATION");
    dumpEnum(writer, blend_equation);
                writer.endMember();
            }
        }



        // GL_POLYGON_OFFSET_FILL
        {
            flushErrors();
    GLboolean polygon_offset_fill_arr[2] = {0, (GLboolean)0xdeadc0de};
    glGetBooleanv(GL_POLYGON_OFFSET_FILL, polygon_offset_fill_arr);
    GLboolean polygon_offset_fill = polygon_offset_fill_arr[0];
    assert(polygon_offset_fill_arr[1] == (GLboolean)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_POLYGON_OFFSET_FILL");
    dumpBoolean(writer, polygon_offset_fill);
                writer.endMember();
            }
        }

        // GL_POLYGON_OFFSET_FACTOR
        {
            flushErrors();
    GLfloat polygon_offset_factor_arr[2] = {0, (GLfloat)0xdeadc0de};
    glGetFloatv(GL_POLYGON_OFFSET_FACTOR, polygon_offset_factor_arr);
    GLfloat polygon_offset_factor = polygon_offset_factor_arr[0];
    assert(polygon_offset_factor_arr[1] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_POLYGON_OFFSET_FACTOR");
    writer.writeFloat(polygon_offset_factor);
                writer.endMember();
            }
        }



        // GL_UNPACK_SKIP_IMAGES
        {
            flushErrors();
    GLint unpack_skip_images_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_UNPACK_SKIP_IMAGES, unpack_skip_images_arr);
    GLint unpack_skip_images = unpack_skip_images_arr[0];
    assert(unpack_skip_images_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_UNPACK_SKIP_IMAGES");
    writer.writeInt(unpack_skip_images);
                writer.endMember();
            }
        }

        // GL_UNPACK_IMAGE_HEIGHT
        {
            flushErrors();
    GLfloat unpack_image_height_arr[2] = {0, (GLfloat)0xdeadc0de};
    glGetFloatv(GL_UNPACK_IMAGE_HEIGHT, unpack_image_height_arr);
    GLfloat unpack_image_height = unpack_image_height_arr[0];
    assert(unpack_image_height_arr[1] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_UNPACK_IMAGE_HEIGHT");
    writer.writeFloat(unpack_image_height);
                writer.endMember();
            }
        }

        // GL_MAX_3D_TEXTURE_SIZE
        {
            flushErrors();
    GLint max_3d_texture_size_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_MAX_3D_TEXTURE_SIZE, max_3d_texture_size_arr);
    GLint max_3d_texture_size = max_3d_texture_size_arr[0];
    assert(max_3d_texture_size_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_MAX_3D_TEXTURE_SIZE");
    writer.writeInt(max_3d_texture_size);
                writer.endMember();
            }
        }



        // GL_SAMPLE_ALPHA_TO_COVERAGE
        {
            flushErrors();
    GLint sample_alpha_to_coverage_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_SAMPLE_ALPHA_TO_COVERAGE, sample_alpha_to_coverage_arr);
    GLint sample_alpha_to_coverage = sample_alpha_to_coverage_arr[0];
    assert(sample_alpha_to_coverage_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_SAMPLE_ALPHA_TO_COVERAGE");
    writer.writeInt(sample_alpha_to_coverage);
                writer.endMember();
            }
        }

        // GL_SAMPLE_COVERAGE
        {
            flushErrors();
    GLint sample_coverage_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_SAMPLE_COVERAGE, sample_coverage_arr);
    GLint sample_coverage = sample_coverage_arr[0];
    assert(sample_coverage_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_SAMPLE_COVERAGE");
    writer.writeInt(sample_coverage);
                writer.endMember();
            }
        }

        // GL_SAMPLE_BUFFERS
        {
            flushErrors();
    GLint sample_buffers_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_SAMPLE_BUFFERS, sample_buffers_arr);
    GLint sample_buffers = sample_buffers_arr[0];
    assert(sample_buffers_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_SAMPLE_BUFFERS");
    writer.writeInt(sample_buffers);
                writer.endMember();
            }
        }

        // GL_SAMPLES
        {
            flushErrors();
    GLint samples_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_SAMPLES, samples_arr);
    GLint samples = samples_arr[0];
    assert(samples_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_SAMPLES");
    writer.writeInt(samples);
                writer.endMember();
            }
        }

        // GL_SAMPLE_COVERAGE_VALUE
        {
            flushErrors();
    GLfloat sample_coverage_value_arr[2] = {0, (GLfloat)0xdeadc0de};
    glGetFloatv(GL_SAMPLE_COVERAGE_VALUE, sample_coverage_value_arr);
    GLfloat sample_coverage_value = sample_coverage_value_arr[0];
    assert(sample_coverage_value_arr[1] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_SAMPLE_COVERAGE_VALUE");
    writer.writeFloat(sample_coverage_value);
                writer.endMember();
            }
        }

        // GL_SAMPLE_COVERAGE_INVERT
        {
            flushErrors();
    GLint sample_coverage_invert_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_SAMPLE_COVERAGE_INVERT, sample_coverage_invert_arr);
    GLint sample_coverage_invert = sample_coverage_invert_arr[0];
    assert(sample_coverage_invert_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_SAMPLE_COVERAGE_INVERT");
    writer.writeInt(sample_coverage_invert);
                writer.endMember();
            }
        }

        // GL_BLEND_DST_RGB
        {
            flushErrors();
    GLint blend_dst_rgb_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_BLEND_DST_RGB, blend_dst_rgb_arr);
    GLint blend_dst_rgb = blend_dst_rgb_arr[0];
    assert(blend_dst_rgb_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BLEND_DST_RGB");
    dumpEnum(writer, blend_dst_rgb);
                writer.endMember();
            }
        }

        // GL_BLEND_SRC_RGB
        {
            flushErrors();
    GLint blend_src_rgb_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_BLEND_SRC_RGB, blend_src_rgb_arr);
    GLint blend_src_rgb = blend_src_rgb_arr[0];
    assert(blend_src_rgb_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BLEND_SRC_RGB");
    dumpEnum(writer, blend_src_rgb);
                writer.endMember();
            }
        }

        // GL_BLEND_DST_ALPHA
        {
            flushErrors();
    GLint blend_dst_alpha_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_BLEND_DST_ALPHA, blend_dst_alpha_arr);
    GLint blend_dst_alpha = blend_dst_alpha_arr[0];
    assert(blend_dst_alpha_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BLEND_DST_ALPHA");
    dumpEnum(writer, blend_dst_alpha);
                writer.endMember();
            }
        }

        // GL_BLEND_SRC_ALPHA
        {
            flushErrors();
    GLint blend_src_alpha_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_BLEND_SRC_ALPHA, blend_src_alpha_arr);
    GLint blend_src_alpha = blend_src_alpha_arr[0];
    assert(blend_src_alpha_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BLEND_SRC_ALPHA");
    dumpEnum(writer, blend_src_alpha);
                writer.endMember();
            }
        }

        // GL_MAX_ELEMENTS_VERTICES
        {
            flushErrors();
    GLint max_elements_vertices_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_MAX_ELEMENTS_VERTICES, max_elements_vertices_arr);
    GLint max_elements_vertices = max_elements_vertices_arr[0];
    assert(max_elements_vertices_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_MAX_ELEMENTS_VERTICES");
    writer.writeInt(max_elements_vertices);
                writer.endMember();
            }
        }

        // GL_MAX_ELEMENTS_INDICES
        {
            flushErrors();
    GLint max_elements_indices_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_MAX_ELEMENTS_INDICES, max_elements_indices_arr);
    GLint max_elements_indices = max_elements_indices_arr[0];
    assert(max_elements_indices_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_MAX_ELEMENTS_INDICES");
    writer.writeInt(max_elements_indices);
                writer.endMember();
            }
        }

        // GL_GENERATE_MIPMAP_HINT
        {
            flushErrors();
    GLint generate_mipmap_hint_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_GENERATE_MIPMAP_HINT, generate_mipmap_hint_arr);
    GLint generate_mipmap_hint = generate_mipmap_hint_arr[0];
    assert(generate_mipmap_hint_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_GENERATE_MIPMAP_HINT");
    dumpEnum(writer, generate_mipmap_hint);
                writer.endMember();
            }
        }


        // GL_MAJOR_VERSION
        {
            flushErrors();
    GLint major_version_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_MAJOR_VERSION, major_version_arr);
    GLint major_version = major_version_arr[0];
    assert(major_version_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_MAJOR_VERSION");
    writer.writeInt(major_version);
                writer.endMember();
            }
        }

        // GL_MINOR_VERSION
        {
            flushErrors();
    GLint minor_version_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_MINOR_VERSION, minor_version_arr);
    GLint minor_version = minor_version_arr[0];
    assert(minor_version_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_MINOR_VERSION");
    writer.writeInt(minor_version);
                writer.endMember();
            }
        }

        // GL_NUM_EXTENSIONS
        {
            flushErrors();
    GLint num_extensions_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_NUM_EXTENSIONS, num_extensions_arr);
    GLint num_extensions = num_extensions_arr[0];
    assert(num_extensions_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_NUM_EXTENSIONS");
    writer.writeInt(num_extensions);
                writer.endMember();
            }
        }



        // GL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED
        {
            flushErrors();
    GLboolean primitive_restart_for_patches_supported_arr[2] = {0, (GLboolean)0xdeadc0de};
    glGetBooleanv(GL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED, primitive_restart_for_patches_supported_arr);
    GLboolean primitive_restart_for_patches_supported = primitive_restart_for_patches_supported_arr[0];
    assert(primitive_restart_for_patches_supported_arr[1] == (GLboolean)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED");
    dumpBoolean(writer, primitive_restart_for_patches_supported);
                writer.endMember();
            }
        }

        // GL_ALIASED_POINT_SIZE_RANGE
        {
            flushErrors();
    GLfloat aliased_point_size_range[2 + 1];
    memset(aliased_point_size_range, 0, 2 * sizeof *aliased_point_size_range);
    aliased_point_size_range[2] = (GLfloat)0xdeadc0de;
    if (2) {
        glGetFloatv(GL_ALIASED_POINT_SIZE_RANGE, aliased_point_size_range);
    }
    assert(aliased_point_size_range[2] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_ALIASED_POINT_SIZE_RANGE");
    writer.beginArray();
    for (unsigned _i45 = 0; _i45 < 2; ++_i45) {
    writer.writeFloat(aliased_point_size_range[_i45]);
    }
    writer.endArray();
                writer.endMember();
            }
        }

        // GL_ALIASED_LINE_WIDTH_RANGE
        {
            flushErrors();
    GLfloat aliased_line_width_range[2 + 1];
    memset(aliased_line_width_range, 0, 2 * sizeof *aliased_line_width_range);
    aliased_line_width_range[2] = (GLfloat)0xdeadc0de;
    if (2) {
        glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, aliased_line_width_range);
    }
    assert(aliased_line_width_range[2] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_ALIASED_LINE_WIDTH_RANGE");
    writer.beginArray();
    for (unsigned _i46 = 0; _i46 < 2; ++_i46) {
    writer.writeFloat(aliased_line_width_range[_i46]);
    }
    writer.endArray();
                writer.endMember();
            }
        }

        // GL_ACTIVE_TEXTURE
        {
            flushErrors();
    GLint active_texture_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_ACTIVE_TEXTURE, active_texture_arr);
    GLint active_texture = active_texture_arr[0];
    assert(active_texture_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_ACTIVE_TEXTURE");
    dumpEnum(writer, active_texture);
                writer.endMember();
            }
        }

        // GL_MAX_RENDERBUFFER_SIZE
        {
            flushErrors();
    GLint max_renderbuffer_size_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, max_renderbuffer_size_arr);
    GLint max_renderbuffer_size = max_renderbuffer_size_arr[0];
    assert(max_renderbuffer_size_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_MAX_RENDERBUFFER_SIZE");
    writer.writeInt(max_renderbuffer_size);
                writer.endMember();
            }
        }



        // GL_MAX_TEXTURE_LOD_BIAS
        {
            flushErrors();
    GLfloat max_texture_lod_bias_arr[2] = {0, (GLfloat)0xdeadc0de};
    glGetFloatv(GL_MAX_TEXTURE_LOD_BIAS, max_texture_lod_bias_arr);
    GLfloat max_texture_lod_bias = max_texture_lod_bias_arr[0];
    assert(max_texture_lod_bias_arr[1] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_MAX_TEXTURE_LOD_BIAS");
    writer.writeFloat(max_texture_lod_bias);
                writer.endMember();
            }
        }

        // GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT
        {
            flushErrors();
    GLfloat max_texture_max_anisotropy_ext_arr[2] = {0, (GLfloat)0xdeadc0de};
    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, max_texture_max_anisotropy_ext_arr);
    GLfloat max_texture_max_anisotropy_ext = max_texture_max_anisotropy_ext_arr[0];
    assert(max_texture_max_anisotropy_ext_arr[1] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT");
    writer.writeFloat(max_texture_max_anisotropy_ext);
                writer.endMember();
            }
        }

        // GL_MAX_CUBE_MAP_TEXTURE_SIZE
        {
            flushErrors();
    GLint max_cube_map_texture_size_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_MAX_CUBE_MAP_TEXTURE_SIZE, max_cube_map_texture_size_arr);
    GLint max_cube_map_texture_size = max_cube_map_texture_size_arr[0];
    assert(max_cube_map_texture_size_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_MAX_CUBE_MAP_TEXTURE_SIZE");
    writer.writeInt(max_cube_map_texture_size);
                writer.endMember();
            }
        }



        // GL_VERTEX_ARRAY_BINDING
        {
            flushErrors();
    GLint vertex_array_binding_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, vertex_array_binding_arr);
    GLint vertex_array_binding = vertex_array_binding_arr[0];
    assert(vertex_array_binding_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_VERTEX_ARRAY_BINDING");
    writer.writeInt(vertex_array_binding);
                writer.endMember();
            }
        }


        // GL_NUM_COMPRESSED_TEXTURE_FORMATS
        {
            flushErrors();
    GLint num_compressed_texture_formats_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_NUM_COMPRESSED_TEXTURE_FORMATS, num_compressed_texture_formats_arr);
    GLint num_compressed_texture_formats = num_compressed_texture_formats_arr[0];
    assert(num_compressed_texture_formats_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_NUM_COMPRESSED_TEXTURE_FORMATS");
    writer.writeInt(num_compressed_texture_formats);
                writer.endMember();
            }
        }

        // GL_COMPRESSED_TEXTURE_FORMATS
        {
            flushErrors();
    size_t _compressed_texture_formats_length = _glGetInteger(GL_NUM_COMPRESSED_TEXTURE_FORMATS);
    GLint *compressed_texture_formats = _allocator.alloc<GLint>(_compressed_texture_formats_length + 1);
    memset(compressed_texture_formats, 0, _compressed_texture_formats_length * sizeof *compressed_texture_formats);
    compressed_texture_formats[_compressed_texture_formats_length] = (GLint)0xdeadc0de;
    if (_compressed_texture_formats_length) {
        glGetIntegerv(GL_COMPRESSED_TEXTURE_FORMATS, compressed_texture_formats);
    }
    assert(compressed_texture_formats[_compressed_texture_formats_length] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_COMPRESSED_TEXTURE_FORMATS");
    writer.beginArray();
    for (unsigned _i54 = 0; _i54 < _glGetInteger(GL_NUM_COMPRESSED_TEXTURE_FORMATS); ++_i54) {
    dumpEnum(writer, compressed_texture_formats[_i54]);
    }
    writer.endArray();
                writer.endMember();
            }
        }

        // GL_NUM_PROGRAM_BINARY_FORMATS
        {
            flushErrors();
    GLint num_program_binary_formats_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_NUM_PROGRAM_BINARY_FORMATS, num_program_binary_formats_arr);
    GLint num_program_binary_formats = num_program_binary_formats_arr[0];
    assert(num_program_binary_formats_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_NUM_PROGRAM_BINARY_FORMATS");
    writer.writeInt(num_program_binary_formats);
                writer.endMember();
            }
        }

        // GL_PROGRAM_BINARY_FORMATS
        {
            flushErrors();
    size_t _program_binary_formats_length = _glGetInteger(GL_NUM_PROGRAM_BINARY_FORMATS);
    GLint *program_binary_formats = _allocator.alloc<GLint>(_program_binary_formats_length + 1);
    memset(program_binary_formats, 0, _program_binary_formats_length * sizeof *program_binary_formats);
    program_binary_formats[_program_binary_formats_length] = (GLint)0xdeadc0de;
    if (_program_binary_formats_length) {
        glGetIntegerv(GL_PROGRAM_BINARY_FORMATS, program_binary_formats);
    }
    assert(program_binary_formats[_program_binary_formats_length] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_PROGRAM_BINARY_FORMATS");
    writer.beginArray();
    for (unsigned _i58 = 0; _i58 < _glGetInteger(GL_NUM_PROGRAM_BINARY_FORMATS); ++_i58) {
    dumpEnum(writer, program_binary_formats[_i58]);
    }
    writer.endArray();
                writer.endMember();
            }
        }

        // GL_STENCIL_BACK_FUNC
        {
            flushErrors();
    GLint stencil_back_func_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_STENCIL_BACK_FUNC, stencil_back_func_arr);
    GLint stencil_back_func = stencil_back_func_arr[0];
    assert(stencil_back_func_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_STENCIL_BACK_FUNC");
    dumpEnum(writer, stencil_back_func);
                writer.endMember();
            }
        }

        // GL_STENCIL_BACK_FAIL
        {
            flushErrors();
    GLint stencil_back_fail_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_STENCIL_BACK_FAIL, stencil_back_fail_arr);
    GLint stencil_back_fail = stencil_back_fail_arr[0];
    assert(stencil_back_fail_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_STENCIL_BACK_FAIL");
    dumpEnum(writer, stencil_back_fail);
                writer.endMember();
            }
        }

        // GL_STENCIL_BACK_PASS_DEPTH_FAIL
        {
            flushErrors();
    GLint stencil_back_pass_depth_fail_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_STENCIL_BACK_PASS_DEPTH_FAIL, stencil_back_pass_depth_fail_arr);
    GLint stencil_back_pass_depth_fail = stencil_back_pass_depth_fail_arr[0];
    assert(stencil_back_pass_depth_fail_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_STENCIL_BACK_PASS_DEPTH_FAIL");
    dumpEnum(writer, stencil_back_pass_depth_fail);
                writer.endMember();
            }
        }

        // GL_STENCIL_BACK_PASS_DEPTH_PASS
        {
            flushErrors();
    GLint stencil_back_pass_depth_pass_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_STENCIL_BACK_PASS_DEPTH_PASS, stencil_back_pass_depth_pass_arr);
    GLint stencil_back_pass_depth_pass = stencil_back_pass_depth_pass_arr[0];
    assert(stencil_back_pass_depth_pass_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_STENCIL_BACK_PASS_DEPTH_PASS");
    dumpEnum(writer, stencil_back_pass_depth_pass);
                writer.endMember();
            }
        }



        // GL_MAX_DRAW_BUFFERS
        {
            flushErrors();
    GLint max_draw_buffers_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_MAX_DRAW_BUFFERS, max_draw_buffers_arr);
    GLint max_draw_buffers = max_draw_buffers_arr[0];
    assert(max_draw_buffers_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_MAX_DRAW_BUFFERS");
    writer.writeInt(max_draw_buffers);
                writer.endMember();
            }
        }

        // GL_DRAW_BUFFER0
        {
            flushErrors();
    GLint draw_buffer0_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_DRAW_BUFFER0, draw_buffer0_arr);
    GLint draw_buffer0 = draw_buffer0_arr[0];
    assert(draw_buffer0_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_DRAW_BUFFER0");
    dumpEnum(writer, draw_buffer0);
                writer.endMember();
            }
        }

        // GL_DRAW_BUFFER1
        {
            flushErrors();
    GLint draw_buffer1_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_DRAW_BUFFER1, draw_buffer1_arr);
    GLint draw_buffer1 = draw_buffer1_arr[0];
    assert(draw_buffer1_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_DRAW_BUFFER1");
    dumpEnum(writer, draw_buffer1);
                writer.endMember();
            }
        }

        // GL_DRAW_BUFFER2
        {
            flushErrors();
    GLint draw_buffer2_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_DRAW_BUFFER2, draw_buffer2_arr);
    GLint draw_buffer2 = draw_buffer2_arr[0];
    assert(draw_buffer2_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_DRAW_BUFFER2");
    dumpEnum(writer, draw_buffer2);
                writer.endMember();
            }
        }

        // GL_DRAW_BUFFER3
        {
            flushErrors();
    GLint draw_buffer3_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_DRAW_BUFFER3, draw_buffer3_arr);
    GLint draw_buffer3 = draw_buffer3_arr[0];
    assert(draw_buffer3_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_DRAW_BUFFER3");
    dumpEnum(writer, draw_buffer3);
                writer.endMember();
            }
        }

        // GL_DRAW_BUFFER4
        {
            flushErrors();
    GLint draw_buffer4_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_DRAW_BUFFER4, draw_buffer4_arr);
    GLint draw_buffer4 = draw_buffer4_arr[0];
    assert(draw_buffer4_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_DRAW_BUFFER4");
    dumpEnum(writer, draw_buffer4);
                writer.endMember();
            }
        }

        // GL_DRAW_BUFFER5
        {
            flushErrors();
    GLint draw_buffer5_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_DRAW_BUFFER5, draw_buffer5_arr);
    GLint draw_buffer5 = draw_buffer5_arr[0];
    assert(draw_buffer5_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_DRAW_BUFFER5");
    dumpEnum(writer, draw_buffer5);
                writer.endMember();
            }
        }

        // GL_DRAW_BUFFER6
        {
            flushErrors();
    GLint draw_buffer6_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_DRAW_BUFFER6, draw_buffer6_arr);
    GLint draw_buffer6 = draw_buffer6_arr[0];
    assert(draw_buffer6_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_DRAW_BUFFER6");
    dumpEnum(writer, draw_buffer6);
                writer.endMember();
            }
        }

        // GL_DRAW_BUFFER7
        {
            flushErrors();
    GLint draw_buffer7_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_DRAW_BUFFER7, draw_buffer7_arr);
    GLint draw_buffer7 = draw_buffer7_arr[0];
    assert(draw_buffer7_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_DRAW_BUFFER7");
    dumpEnum(writer, draw_buffer7);
                writer.endMember();
            }
        }

        // GL_DRAW_BUFFER8
        {
            flushErrors();
    GLint draw_buffer8_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_DRAW_BUFFER8, draw_buffer8_arr);
    GLint draw_buffer8 = draw_buffer8_arr[0];
    assert(draw_buffer8_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_DRAW_BUFFER8");
    dumpEnum(writer, draw_buffer8);
                writer.endMember();
            }
        }

        // GL_DRAW_BUFFER9
        {
            flushErrors();
    GLint draw_buffer9_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_DRAW_BUFFER9, draw_buffer9_arr);
    GLint draw_buffer9 = draw_buffer9_arr[0];
    assert(draw_buffer9_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_DRAW_BUFFER9");
    dumpEnum(writer, draw_buffer9);
                writer.endMember();
            }
        }

        // GL_DRAW_BUFFER10
        {
            flushErrors();
    GLint draw_buffer10_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_DRAW_BUFFER10, draw_buffer10_arr);
    GLint draw_buffer10 = draw_buffer10_arr[0];
    assert(draw_buffer10_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_DRAW_BUFFER10");
    dumpEnum(writer, draw_buffer10);
                writer.endMember();
            }
        }

        // GL_DRAW_BUFFER11
        {
            flushErrors();
    GLint draw_buffer11_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_DRAW_BUFFER11, draw_buffer11_arr);
    GLint draw_buffer11 = draw_buffer11_arr[0];
    assert(draw_buffer11_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_DRAW_BUFFER11");
    dumpEnum(writer, draw_buffer11);
                writer.endMember();
            }
        }

        // GL_DRAW_BUFFER12
        {
            flushErrors();
    GLint draw_buffer12_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_DRAW_BUFFER12, draw_buffer12_arr);
    GLint draw_buffer12 = draw_buffer12_arr[0];
    assert(draw_buffer12_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_DRAW_BUFFER12");
    dumpEnum(writer, draw_buffer12);
                writer.endMember();
            }
        }

        // GL_DRAW_BUFFER13
        {
            flushErrors();
    GLint draw_buffer13_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_DRAW_BUFFER13, draw_buffer13_arr);
    GLint draw_buffer13 = draw_buffer13_arr[0];
    assert(draw_buffer13_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_DRAW_BUFFER13");
    dumpEnum(writer, draw_buffer13);
                writer.endMember();
            }
        }

        // GL_DRAW_BUFFER14
        {
            flushErrors();
    GLint draw_buffer14_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_DRAW_BUFFER14, draw_buffer14_arr);
    GLint draw_buffer14 = draw_buffer14_arr[0];
    assert(draw_buffer14_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_DRAW_BUFFER14");
    dumpEnum(writer, draw_buffer14);
                writer.endMember();
            }
        }

        // GL_DRAW_BUFFER15
        {
            flushErrors();
    GLint draw_buffer15_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_DRAW_BUFFER15, draw_buffer15_arr);
    GLint draw_buffer15 = draw_buffer15_arr[0];
    assert(draw_buffer15_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_DRAW_BUFFER15");
    dumpEnum(writer, draw_buffer15);
                writer.endMember();
            }
        }

        // GL_BLEND_EQUATION_ALPHA
        {
            flushErrors();
    GLint blend_equation_alpha_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_BLEND_EQUATION_ALPHA, blend_equation_alpha_arr);
    GLint blend_equation_alpha = blend_equation_alpha_arr[0];
    assert(blend_equation_alpha_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BLEND_EQUATION_ALPHA");
    dumpEnum(writer, blend_equation_alpha);
                writer.endMember();
            }
        }


        // GL_MAX_VERTEX_ATTRIBS
        {
            flushErrors();
    GLint max_vertex_attribs_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, max_vertex_attribs_arr);
    GLint max_vertex_attribs = max_vertex_attribs_arr[0];
    assert(max_vertex_attribs_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_MAX_VERTEX_ATTRIBS");
    writer.writeInt(max_vertex_attribs);
                writer.endMember();
            }
        }


        // GL_MAX_TEXTURE_IMAGE_UNITS
        {
            flushErrors();
    GLint max_texture_image_units_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, max_texture_image_units_arr);
    GLint max_texture_image_units = max_texture_image_units_arr[0];
    assert(max_texture_image_units_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_MAX_TEXTURE_IMAGE_UNITS");
    writer.writeInt(max_texture_image_units);
                writer.endMember();
            }
        }

        // GL_ARRAY_BUFFER_BINDING
        {
            flushErrors();
    GLint array_buffer_binding_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_ARRAY_BUFFER_BINDING, array_buffer_binding_arr);
    GLint array_buffer_binding = array_buffer_binding_arr[0];
    assert(array_buffer_binding_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_ARRAY_BUFFER_BINDING");
    writer.writeInt(array_buffer_binding);
                writer.endMember();
            }
        }

        // GL_ELEMENT_ARRAY_BUFFER_BINDING
        {
            flushErrors();
    GLint element_array_buffer_binding_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, element_array_buffer_binding_arr);
    GLint element_array_buffer_binding = element_array_buffer_binding_arr[0];
    assert(element_array_buffer_binding_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_ELEMENT_ARRAY_BUFFER_BINDING");
    writer.writeInt(element_array_buffer_binding);
                writer.endMember();
            }
        }



        // GL_PIXEL_PACK_BUFFER_BINDING
        {
            flushErrors();
    GLint pixel_pack_buffer_binding_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_PIXEL_PACK_BUFFER_BINDING, pixel_pack_buffer_binding_arr);
    GLint pixel_pack_buffer_binding = pixel_pack_buffer_binding_arr[0];
    assert(pixel_pack_buffer_binding_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_PIXEL_PACK_BUFFER_BINDING");
    writer.writeInt(pixel_pack_buffer_binding);
                writer.endMember();
            }
        }

        // GL_PIXEL_UNPACK_BUFFER_BINDING
        {
            flushErrors();
    GLint pixel_unpack_buffer_binding_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_PIXEL_UNPACK_BUFFER_BINDING, pixel_unpack_buffer_binding_arr);
    GLint pixel_unpack_buffer_binding = pixel_unpack_buffer_binding_arr[0];
    assert(pixel_unpack_buffer_binding_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_PIXEL_UNPACK_BUFFER_BINDING");
    writer.writeInt(pixel_unpack_buffer_binding);
                writer.endMember();
            }
        }



        // GL_MAX_ARRAY_TEXTURE_LAYERS
        {
            flushErrors();
    GLint max_array_texture_layers_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_MAX_ARRAY_TEXTURE_LAYERS, max_array_texture_layers_arr);
    GLint max_array_texture_layers = max_array_texture_layers_arr[0];
    assert(max_array_texture_layers_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_MAX_ARRAY_TEXTURE_LAYERS");
    writer.writeInt(max_array_texture_layers);
                writer.endMember();
            }
        }

        // GL_MIN_PROGRAM_TEXEL_OFFSET
        {
            flushErrors();
    GLfloat min_program_texel_offset_arr[2] = {0, (GLfloat)0xdeadc0de};
    glGetFloatv(GL_MIN_PROGRAM_TEXEL_OFFSET, min_program_texel_offset_arr);
    GLfloat min_program_texel_offset = min_program_texel_offset_arr[0];
    assert(min_program_texel_offset_arr[1] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_MIN_PROGRAM_TEXEL_OFFSET");
    writer.writeFloat(min_program_texel_offset);
                writer.endMember();
            }
        }

        // GL_MAX_PROGRAM_TEXEL_OFFSET
        {
            flushErrors();
    GLfloat max_program_texel_offset_arr[2] = {0, (GLfloat)0xdeadc0de};
    glGetFloatv(GL_MAX_PROGRAM_TEXEL_OFFSET, max_program_texel_offset_arr);
    GLfloat max_program_texel_offset = max_program_texel_offset_arr[0];
    assert(max_program_texel_offset_arr[1] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_MAX_PROGRAM_TEXEL_OFFSET");
    writer.writeFloat(max_program_texel_offset);
                writer.endMember();
            }
        }



        // GL_UNIFORM_BUFFER_BINDING
        {
            flushErrors();
    GLint uniform_buffer_binding_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_UNIFORM_BUFFER_BINDING, uniform_buffer_binding_arr);
    GLint uniform_buffer_binding = uniform_buffer_binding_arr[0];
    assert(uniform_buffer_binding_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_UNIFORM_BUFFER_BINDING");
    writer.writeInt(uniform_buffer_binding);
                writer.endMember();
            }
        }

        // GL_MAX_VERTEX_UNIFORM_BLOCKS
        {
            flushErrors();
    GLint max_vertex_uniform_blocks_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_MAX_VERTEX_UNIFORM_BLOCKS, max_vertex_uniform_blocks_arr);
    GLint max_vertex_uniform_blocks = max_vertex_uniform_blocks_arr[0];
    assert(max_vertex_uniform_blocks_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_MAX_VERTEX_UNIFORM_BLOCKS");
    writer.writeInt(max_vertex_uniform_blocks);
                writer.endMember();
            }
        }

        // GL_MAX_FRAGMENT_UNIFORM_BLOCKS
        {
            flushErrors();
    GLint max_fragment_uniform_blocks_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_BLOCKS, max_fragment_uniform_blocks_arr);
    GLint max_fragment_uniform_blocks = max_fragment_uniform_blocks_arr[0];
    assert(max_fragment_uniform_blocks_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_MAX_FRAGMENT_UNIFORM_BLOCKS");
    writer.writeInt(max_fragment_uniform_blocks);
                writer.endMember();
            }
        }

        // GL_MAX_COMBINED_UNIFORM_BLOCKS
        {
            flushErrors();
    GLint max_combined_uniform_blocks_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_MAX_COMBINED_UNIFORM_BLOCKS, max_combined_uniform_blocks_arr);
    GLint max_combined_uniform_blocks = max_combined_uniform_blocks_arr[0];
    assert(max_combined_uniform_blocks_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_MAX_COMBINED_UNIFORM_BLOCKS");
    writer.writeInt(max_combined_uniform_blocks);
                writer.endMember();
            }
        }

        // GL_MAX_UNIFORM_BUFFER_BINDINGS
        {
            flushErrors();
    GLint max_uniform_buffer_bindings_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_MAX_UNIFORM_BUFFER_BINDINGS, max_uniform_buffer_bindings_arr);
    GLint max_uniform_buffer_bindings = max_uniform_buffer_bindings_arr[0];
    assert(max_uniform_buffer_bindings_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_MAX_UNIFORM_BUFFER_BINDINGS");
    writer.writeInt(max_uniform_buffer_bindings);
                writer.endMember();
            }
        }

        // GL_MAX_UNIFORM_BLOCK_SIZE
        {
            flushErrors();
    GLint max_uniform_block_size_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, max_uniform_block_size_arr);
    GLint max_uniform_block_size = max_uniform_block_size_arr[0];
    assert(max_uniform_block_size_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_MAX_UNIFORM_BLOCK_SIZE");
    writer.writeInt(max_uniform_block_size);
                writer.endMember();
            }
        }

        // GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS
        {
            flushErrors();
    GLint max_combined_vertex_uniform_components_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS, max_combined_vertex_uniform_components_arr);
    GLint max_combined_vertex_uniform_components = max_combined_vertex_uniform_components_arr[0];
    assert(max_combined_vertex_uniform_components_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS");
    writer.writeInt(max_combined_vertex_uniform_components);
                writer.endMember();
            }
        }

        // GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS
        {
            flushErrors();
    GLint max_combined_fragment_uniform_components_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS, max_combined_fragment_uniform_components_arr);
    GLint max_combined_fragment_uniform_components = max_combined_fragment_uniform_components_arr[0];
    assert(max_combined_fragment_uniform_components_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS");
    writer.writeInt(max_combined_fragment_uniform_components);
                writer.endMember();
            }
        }

        // GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT
        {
            flushErrors();
    GLint uniform_buffer_offset_alignment_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT, uniform_buffer_offset_alignment_arr);
    GLint uniform_buffer_offset_alignment = uniform_buffer_offset_alignment_arr[0];
    assert(uniform_buffer_offset_alignment_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT");
    writer.writeInt(uniform_buffer_offset_alignment);
                writer.endMember();
            }
        }

        // GL_MAX_FRAGMENT_UNIFORM_COMPONENTS
        {
            flushErrors();
    GLint max_fragment_uniform_components_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS, max_fragment_uniform_components_arr);
    GLint max_fragment_uniform_components = max_fragment_uniform_components_arr[0];
    assert(max_fragment_uniform_components_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_MAX_FRAGMENT_UNIFORM_COMPONENTS");
    writer.writeInt(max_fragment_uniform_components);
                writer.endMember();
            }
        }

        // GL_MAX_VERTEX_UNIFORM_COMPONENTS
        {
            flushErrors();
    GLint max_vertex_uniform_components_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS, max_vertex_uniform_components_arr);
    GLint max_vertex_uniform_components = max_vertex_uniform_components_arr[0];
    assert(max_vertex_uniform_components_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_MAX_VERTEX_UNIFORM_COMPONENTS");
    writer.writeInt(max_vertex_uniform_components);
                writer.endMember();
            }
        }

        // GL_MAX_VARYING_COMPONENTS
        {
            flushErrors();
    GLint max_varying_components_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_MAX_VARYING_COMPONENTS, max_varying_components_arr);
    GLint max_varying_components = max_varying_components_arr[0];
    assert(max_varying_components_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_MAX_VARYING_COMPONENTS");
    writer.writeInt(max_varying_components);
                writer.endMember();
            }
        }

        // GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS
        {
            flushErrors();
    GLint max_vertex_texture_image_units_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, max_vertex_texture_image_units_arr);
    GLint max_vertex_texture_image_units = max_vertex_texture_image_units_arr[0];
    assert(max_vertex_texture_image_units_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS");
    writer.writeInt(max_vertex_texture_image_units);
                writer.endMember();
            }
        }

        // GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS
        {
            flushErrors();
    GLint max_combined_texture_image_units_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, max_combined_texture_image_units_arr);
    GLint max_combined_texture_image_units = max_combined_texture_image_units_arr[0];
    assert(max_combined_texture_image_units_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS");
    writer.writeInt(max_combined_texture_image_units);
                writer.endMember();
            }
        }

        // GL_SHADING_LANGUAGE_VERSION
        {
            flushErrors();
    char * shading_language_version = (char *)glGetString(GL_SHADING_LANGUAGE_VERSION);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_SHADING_LANGUAGE_VERSION");
    writer.writeString((const char *)shading_language_version);
                writer.endMember();
            }
        }

        // GL_CURRENT_PROGRAM
        {
            flushErrors();
    GLint current_program_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_CURRENT_PROGRAM, current_program_arr);
    GLint current_program = current_program_arr[0];
    assert(current_program_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_CURRENT_PROGRAM");
    writer.writeInt(current_program);
                writer.endMember();
            }
        }

        // GL_IMPLEMENTATION_COLOR_READ_TYPE
        {
            flushErrors();
    GLint implementation_color_read_type_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_IMPLEMENTATION_COLOR_READ_TYPE, implementation_color_read_type_arr);
    GLint implementation_color_read_type = implementation_color_read_type_arr[0];
    assert(implementation_color_read_type_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_IMPLEMENTATION_COLOR_READ_TYPE");
    dumpEnum(writer, implementation_color_read_type);
                writer.endMember();
            }
        }

        // GL_IMPLEMENTATION_COLOR_READ_FORMAT
        {
            flushErrors();
    GLint implementation_color_read_format_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_IMPLEMENTATION_COLOR_READ_FORMAT, implementation_color_read_format_arr);
    GLint implementation_color_read_format = implementation_color_read_format_arr[0];
    assert(implementation_color_read_format_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_IMPLEMENTATION_COLOR_READ_FORMAT");
    dumpEnum(writer, implementation_color_read_format);
                writer.endMember();
            }
        }



        // GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS
        {
            flushErrors();
    GLint max_transform_feedback_separate_components_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS, max_transform_feedback_separate_components_arr);
    GLint max_transform_feedback_separate_components = max_transform_feedback_separate_components_arr[0];
    assert(max_transform_feedback_separate_components_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS");
    writer.writeInt(max_transform_feedback_separate_components);
                writer.endMember();
            }
        }

        // GL_RASTERIZER_DISCARD
        {
            flushErrors();
    GLboolean rasterizer_discard_arr[2] = {0, (GLboolean)0xdeadc0de};
    glGetBooleanv(GL_RASTERIZER_DISCARD, rasterizer_discard_arr);
    GLboolean rasterizer_discard = rasterizer_discard_arr[0];
    assert(rasterizer_discard_arr[1] == (GLboolean)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_RASTERIZER_DISCARD");
    dumpBoolean(writer, rasterizer_discard);
                writer.endMember();
            }
        }

        // GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS
        {
            flushErrors();
    GLint max_transform_feedback_interleaved_components_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS, max_transform_feedback_interleaved_components_arr);
    GLint max_transform_feedback_interleaved_components = max_transform_feedback_interleaved_components_arr[0];
    assert(max_transform_feedback_interleaved_components_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS");
    writer.writeInt(max_transform_feedback_interleaved_components);
                writer.endMember();
            }
        }

        // GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS
        {
            flushErrors();
    GLint max_transform_feedback_separate_attribs_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS, max_transform_feedback_separate_attribs_arr);
    GLint max_transform_feedback_separate_attribs = max_transform_feedback_separate_attribs_arr[0];
    assert(max_transform_feedback_separate_attribs_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS");
    writer.writeInt(max_transform_feedback_separate_attribs);
                writer.endMember();
            }
        }

        // GL_TRANSFORM_FEEDBACK_BUFFER_BINDING
        {
            flushErrors();
    GLint transform_feedback_buffer_binding_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_TRANSFORM_FEEDBACK_BUFFER_BINDING, transform_feedback_buffer_binding_arr);
    GLint transform_feedback_buffer_binding = transform_feedback_buffer_binding_arr[0];
    assert(transform_feedback_buffer_binding_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_TRANSFORM_FEEDBACK_BUFFER_BINDING");
    writer.writeInt(transform_feedback_buffer_binding);
                writer.endMember();
            }
        }



        // GL_DRAW_FRAMEBUFFER_BINDING
        {
            flushErrors();
    GLint draw_framebuffer_binding_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, draw_framebuffer_binding_arr);
    GLint draw_framebuffer_binding = draw_framebuffer_binding_arr[0];
    assert(draw_framebuffer_binding_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_DRAW_FRAMEBUFFER_BINDING");
    writer.writeInt(draw_framebuffer_binding);
                writer.endMember();
            }
        }

        // GL_RENDERBUFFER_BINDING
        {
            flushErrors();
    GLint renderbuffer_binding_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_RENDERBUFFER_BINDING, renderbuffer_binding_arr);
    GLint renderbuffer_binding = renderbuffer_binding_arr[0];
    assert(renderbuffer_binding_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_RENDERBUFFER_BINDING");
    writer.writeInt(renderbuffer_binding);
                writer.endMember();
            }
        }

        // GL_READ_FRAMEBUFFER_BINDING
        {
            flushErrors();
    GLint read_framebuffer_binding_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, read_framebuffer_binding_arr);
    GLint read_framebuffer_binding = read_framebuffer_binding_arr[0];
    assert(read_framebuffer_binding_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_READ_FRAMEBUFFER_BINDING");
    writer.writeInt(read_framebuffer_binding);
                writer.endMember();
            }
        }

        // GL_MAX_COLOR_ATTACHMENTS
        {
            flushErrors();
    GLint max_color_attachments_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, max_color_attachments_arr);
    GLint max_color_attachments = max_color_attachments_arr[0];
    assert(max_color_attachments_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_MAX_COLOR_ATTACHMENTS");
    writer.writeInt(max_color_attachments);
                writer.endMember();
            }
        }

        // GL_MAX_SAMPLES
        {
            flushErrors();
    GLint max_samples_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_MAX_SAMPLES, max_samples_arr);
    GLint max_samples = max_samples_arr[0];
    assert(max_samples_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_MAX_SAMPLES");
    writer.writeInt(max_samples);
                writer.endMember();
            }
        }

        // GL_PRIMITIVE_RESTART_FIXED_INDEX
        {
            flushErrors();
    GLboolean primitive_restart_fixed_index_arr[2] = {0, (GLboolean)0xdeadc0de};
    glGetBooleanv(GL_PRIMITIVE_RESTART_FIXED_INDEX, primitive_restart_fixed_index_arr);
    GLboolean primitive_restart_fixed_index = primitive_restart_fixed_index_arr[0];
    assert(primitive_restart_fixed_index_arr[1] == (GLboolean)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_PRIMITIVE_RESTART_FIXED_INDEX");
    dumpBoolean(writer, primitive_restart_fixed_index);
                writer.endMember();
            }
        }

        // GL_MAX_ELEMENT_INDEX
        {
            flushErrors();
    GLint max_element_index_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_MAX_ELEMENT_INDEX, max_element_index_arr);
    GLint max_element_index = max_element_index_arr[0];
    assert(max_element_index_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_MAX_ELEMENT_INDEX");
    writer.writeInt(max_element_index);
                writer.endMember();
            }
        }


        // GL_SHADER_BINARY_FORMATS
        {
            flushErrors();
    size_t _shader_binary_formats_length = _glGetInteger(GL_NUM_SHADER_BINARY_FORMATS);
    GLint *shader_binary_formats = _allocator.alloc<GLint>(_shader_binary_formats_length + 1);
    memset(shader_binary_formats, 0, _shader_binary_formats_length * sizeof *shader_binary_formats);
    shader_binary_formats[_shader_binary_formats_length] = (GLint)0xdeadc0de;
    if (_shader_binary_formats_length) {
        glGetIntegerv(GL_SHADER_BINARY_FORMATS, shader_binary_formats);
    }
    assert(shader_binary_formats[_shader_binary_formats_length] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_SHADER_BINARY_FORMATS");
    writer.beginArray();
    for (unsigned _i61 = 0; _i61 < _glGetInteger(GL_NUM_SHADER_BINARY_FORMATS); ++_i61) {
    dumpEnum(writer, shader_binary_formats[_i61]);
    }
    writer.endArray();
                writer.endMember();
            }
        }

        // GL_NUM_SHADER_BINARY_FORMATS
        {
            flushErrors();
    GLint num_shader_binary_formats_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_NUM_SHADER_BINARY_FORMATS, num_shader_binary_formats_arr);
    GLint num_shader_binary_formats = num_shader_binary_formats_arr[0];
    assert(num_shader_binary_formats_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_NUM_SHADER_BINARY_FORMATS");
    writer.writeInt(num_shader_binary_formats);
                writer.endMember();
            }
        }

        // GL_SHADER_COMPILER
        {
            flushErrors();
    GLboolean shader_compiler_arr[2] = {0, (GLboolean)0xdeadc0de};
    glGetBooleanv(GL_SHADER_COMPILER, shader_compiler_arr);
    GLboolean shader_compiler = shader_compiler_arr[0];
    assert(shader_compiler_arr[1] == (GLboolean)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_SHADER_COMPILER");
    dumpBoolean(writer, shader_compiler);
                writer.endMember();
            }
        }

        // GL_MAX_VERTEX_UNIFORM_VECTORS
        {
            flushErrors();
    GLint max_vertex_uniform_vectors_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_MAX_VERTEX_UNIFORM_VECTORS, max_vertex_uniform_vectors_arr);
    GLint max_vertex_uniform_vectors = max_vertex_uniform_vectors_arr[0];
    assert(max_vertex_uniform_vectors_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_MAX_VERTEX_UNIFORM_VECTORS");
    writer.writeInt(max_vertex_uniform_vectors);
                writer.endMember();
            }
        }

        // GL_MAX_VARYING_VECTORS
        {
            flushErrors();
    GLint max_varying_vectors_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_MAX_VARYING_VECTORS, max_varying_vectors_arr);
    GLint max_varying_vectors = max_varying_vectors_arr[0];
    assert(max_varying_vectors_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_MAX_VARYING_VECTORS");
    writer.writeInt(max_varying_vectors);
                writer.endMember();
            }
        }

        // GL_MAX_FRAGMENT_UNIFORM_VECTORS
        {
            flushErrors();
    GLint max_fragment_uniform_vectors_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_VECTORS, max_fragment_uniform_vectors_arr);
    GLint max_fragment_uniform_vectors = max_fragment_uniform_vectors_arr[0];
    assert(max_fragment_uniform_vectors_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_MAX_FRAGMENT_UNIFORM_VECTORS");
    writer.writeInt(max_fragment_uniform_vectors);
                writer.endMember();
            }
        }



        // GL_TRANSFORM_FEEDBACK_BINDING
        {
            flushErrors();
    GLint transform_feedback_binding_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_TRANSFORM_FEEDBACK_BINDING, transform_feedback_binding_arr);
    GLint transform_feedback_binding = transform_feedback_binding_arr[0];
    assert(transform_feedback_binding_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_TRANSFORM_FEEDBACK_BINDING");
    writer.writeInt(transform_feedback_binding);
                writer.endMember();
            }
        }


        // GL_WINDOW_RECTANGLE_MODE_EXT
        {
            flushErrors();
    GLint window_rectangle_mode_ext_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_WINDOW_RECTANGLE_MODE_EXT, window_rectangle_mode_ext_arr);
    GLint window_rectangle_mode_ext = window_rectangle_mode_ext_arr[0];
    assert(window_rectangle_mode_ext_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_WINDOW_RECTANGLE_MODE_EXT");
    dumpEnum(writer, window_rectangle_mode_ext);
                writer.endMember();
            }
        }

        // GL_MAX_WINDOW_RECTANGLES_EXT
        {
            flushErrors();
    GLint max_window_rectangles_ext_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_MAX_WINDOW_RECTANGLES_EXT, max_window_rectangles_ext_arr);
    GLint max_window_rectangles_ext = max_window_rectangles_ext_arr[0];
    assert(max_window_rectangles_ext_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_MAX_WINDOW_RECTANGLES_EXT");
    writer.writeInt(max_window_rectangles_ext);
                writer.endMember();
            }
        }

        // GL_NUM_WINDOW_RECTANGLES_EXT
        {
            flushErrors();
    GLint num_window_rectangles_ext_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_NUM_WINDOW_RECTANGLES_EXT, num_window_rectangles_ext_arr);
    GLint num_window_rectangles_ext = num_window_rectangles_ext_arr[0];
    assert(num_window_rectangles_ext_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_NUM_WINDOW_RECTANGLES_EXT");
    writer.writeInt(num_window_rectangles_ext);
                writer.endMember();
            }
        }

        // GL_COPY_READ_BUFFER
        {
            flushErrors();
    GLint copy_read_buffer_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_COPY_READ_BUFFER, copy_read_buffer_arr);
    GLint copy_read_buffer = copy_read_buffer_arr[0];
    assert(copy_read_buffer_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_COPY_READ_BUFFER");
    writer.writeInt(copy_read_buffer);
                writer.endMember();
            }
        }

        // GL_COPY_WRITE_BUFFER
        {
            flushErrors();
    GLint copy_write_buffer_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_COPY_WRITE_BUFFER, copy_write_buffer_arr);
    GLint copy_write_buffer = copy_write_buffer_arr[0];
    assert(copy_write_buffer_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_COPY_WRITE_BUFFER");
    writer.writeInt(copy_write_buffer);
                writer.endMember();
            }
        }

        // GL_MAX_VERTEX_OUTPUT_COMPONENTS
        {
            flushErrors();
    GLint max_vertex_output_components_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_MAX_VERTEX_OUTPUT_COMPONENTS, max_vertex_output_components_arr);
    GLint max_vertex_output_components = max_vertex_output_components_arr[0];
    assert(max_vertex_output_components_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_MAX_VERTEX_OUTPUT_COMPONENTS");
    writer.writeInt(max_vertex_output_components);
                writer.endMember();
            }
        }


        // GL_MAX_FRAGMENT_INPUT_COMPONENTS
        {
            flushErrors();
    GLint max_fragment_input_components_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_MAX_FRAGMENT_INPUT_COMPONENTS, max_fragment_input_components_arr);
    GLint max_fragment_input_components = max_fragment_input_components_arr[0];
    assert(max_fragment_input_components_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_MAX_FRAGMENT_INPUT_COMPONENTS");
    writer.writeInt(max_fragment_input_components);
                writer.endMember();
            }
        }



        // GL_PRIMITIVE_BOUNDING_BOX_EXT
        {
            flushErrors();
    GLfloat primitive_bounding_box_ext[8 + 1];
    memset(primitive_bounding_box_ext, 0, 8 * sizeof *primitive_bounding_box_ext);
    primitive_bounding_box_ext[8] = (GLfloat)0xdeadc0de;
    if (8) {
        glGetFloatv(GL_PRIMITIVE_BOUNDING_BOX_EXT, primitive_bounding_box_ext);
    }
    assert(primitive_bounding_box_ext[8] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_PRIMITIVE_BOUNDING_BOX_EXT");
    writer.beginArray();
    for (unsigned _i66 = 0; _i66 < 8; ++_i66) {
    writer.writeFloat(primitive_bounding_box_ext[_i66]);
    }
    writer.endArray();
                writer.endMember();
            }
        }




    GLint max_vertex_attribs = 0;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &max_vertex_attribs);
    for (GLint index = 0; index < max_vertex_attribs; ++index) {
        std::string name = std::string("GL_VERTEX_ATTRIB_ARRAY") + std::to_string(index);
        writer.beginMember(name);
        writer.beginObject();

        // GL_VERTEX_ATTRIB_ARRAY_ENABLED
        {
            flushErrors();
    GLint vertex_attrib_array_enabled_arr[2] = {0, (GLint)0xdeadc0de};
    glGetVertexAttribiv(index, GL_VERTEX_ATTRIB_ARRAY_ENABLED, vertex_attrib_array_enabled_arr);
    GLint vertex_attrib_array_enabled = vertex_attrib_array_enabled_arr[0];
    assert(vertex_attrib_array_enabled_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_VERTEX_ATTRIB_ARRAY_ENABLED");
    dumpBoolean(writer, vertex_attrib_array_enabled);
                writer.endMember();
            }
        }

        // GL_VERTEX_ATTRIB_ARRAY_SIZE
        {
            flushErrors();
    GLint vertex_attrib_array_size_arr[2] = {0, (GLint)0xdeadc0de};
    glGetVertexAttribiv(index, GL_VERTEX_ATTRIB_ARRAY_SIZE, vertex_attrib_array_size_arr);
    GLint vertex_attrib_array_size = vertex_attrib_array_size_arr[0];
    assert(vertex_attrib_array_size_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_VERTEX_ATTRIB_ARRAY_SIZE");
    writer.writeInt(vertex_attrib_array_size);
                writer.endMember();
            }
        }

        // GL_VERTEX_ATTRIB_ARRAY_STRIDE
        {
            flushErrors();
    GLint vertex_attrib_array_stride_arr[2] = {0, (GLint)0xdeadc0de};
    glGetVertexAttribiv(index, GL_VERTEX_ATTRIB_ARRAY_STRIDE, vertex_attrib_array_stride_arr);
    GLint vertex_attrib_array_stride = vertex_attrib_array_stride_arr[0];
    assert(vertex_attrib_array_stride_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_VERTEX_ATTRIB_ARRAY_STRIDE");
    writer.writeInt(vertex_attrib_array_stride);
                writer.endMember();
            }
        }

        // GL_VERTEX_ATTRIB_ARRAY_TYPE
        {
            flushErrors();
    GLint vertex_attrib_array_type_arr[2] = {0, (GLint)0xdeadc0de};
    glGetVertexAttribiv(index, GL_VERTEX_ATTRIB_ARRAY_TYPE, vertex_attrib_array_type_arr);
    GLint vertex_attrib_array_type = vertex_attrib_array_type_arr[0];
    assert(vertex_attrib_array_type_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_VERTEX_ATTRIB_ARRAY_TYPE");
    dumpEnum(writer, vertex_attrib_array_type);
                writer.endMember();
            }
        }

        // GL_CURRENT_VERTEX_ATTRIB
        {
            flushErrors();
    GLfloat current_vertex_attrib[4 + 1];
    memset(current_vertex_attrib, 0, 4 * sizeof *current_vertex_attrib);
    current_vertex_attrib[4] = (GLfloat)0xdeadc0de;
    if (4) {
        glGetVertexAttribfv(index, GL_CURRENT_VERTEX_ATTRIB, current_vertex_attrib);
    }
    assert(current_vertex_attrib[4] == (GLdouble)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_CURRENT_VERTEX_ATTRIB");
    writer.beginArray();
    for (unsigned _i83 = 0; _i83 < 4; ++_i83) {
    writer.writeFloat(current_vertex_attrib[_i83]);
    }
    writer.endArray();
                writer.endMember();
            }
        }

        // GL_VERTEX_ATTRIB_ARRAY_POINTER
        {
            flushErrors();
    GLvoid *vertex_attrib_array_pointer;
    glGetVertexAttribPointerv(index, GL_VERTEX_ATTRIB_ARRAY_POINTER, &vertex_attrib_array_pointer);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_VERTEX_ATTRIB_ARRAY_POINTER");
    writer.writeInt((size_t)vertex_attrib_array_pointer);
                writer.endMember();
            }
        }



        // GL_VERTEX_ATTRIB_ARRAY_NORMALIZED
        {
            flushErrors();
    GLint vertex_attrib_array_normalized_arr[2] = {0, (GLint)0xdeadc0de};
    glGetVertexAttribiv(index, GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, vertex_attrib_array_normalized_arr);
    GLint vertex_attrib_array_normalized = vertex_attrib_array_normalized_arr[0];
    assert(vertex_attrib_array_normalized_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_VERTEX_ATTRIB_ARRAY_NORMALIZED");
    dumpBoolean(writer, vertex_attrib_array_normalized);
                writer.endMember();
            }
        }

        // GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING
        {
            flushErrors();
    GLint vertex_attrib_array_buffer_binding_arr[2] = {0, (GLint)0xdeadc0de};
    glGetVertexAttribiv(index, GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING, vertex_attrib_array_buffer_binding_arr);
    GLint vertex_attrib_array_buffer_binding = vertex_attrib_array_buffer_binding_arr[0];
    assert(vertex_attrib_array_buffer_binding_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING");
    writer.writeInt(vertex_attrib_array_buffer_binding);
                writer.endMember();
            }
        }

        // GL_VERTEX_ATTRIB_ARRAY_INTEGER
        {
            flushErrors();
    GLint vertex_attrib_array_integer_arr[2] = {0, (GLint)0xdeadc0de};
    glGetVertexAttribiv(index, GL_VERTEX_ATTRIB_ARRAY_INTEGER, vertex_attrib_array_integer_arr);
    GLint vertex_attrib_array_integer = vertex_attrib_array_integer_arr[0];
    assert(vertex_attrib_array_integer_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_VERTEX_ATTRIB_ARRAY_INTEGER");
    dumpBoolean(writer, vertex_attrib_array_integer);
                writer.endMember();
            }
        }

        // GL_VERTEX_ATTRIB_ARRAY_DIVISOR
        {
            flushErrors();
    GLint vertex_attrib_array_divisor_arr[2] = {0, (GLint)0xdeadc0de};
    glGetVertexAttribiv(index, GL_VERTEX_ATTRIB_ARRAY_DIVISOR, vertex_attrib_array_divisor_arr);
    GLint vertex_attrib_array_divisor = vertex_attrib_array_divisor_arr[0];
    assert(vertex_attrib_array_divisor_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_VERTEX_ATTRIB_ARRAY_DIVISOR");
    writer.writeInt(vertex_attrib_array_divisor);
                writer.endMember();
            }
        }

        GLint buffer_binding = 0;
        glGetVertexAttribiv(index, GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING, &buffer_binding);
        writer.endObject();
        writer.endMember(); // GL_VERTEX_ATTRIB_ARRAYi
    }


    // GL_ARRAY_BUFFER
    {
        writer.beginMember("GL_ARRAY_BUFFER");
        writer.beginObject();
        GLint buffer = 0;
        glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &buffer);
        if (buffer) {

        // GL_BUFFER_SIZE
        {
            flushErrors();
    GLint buffer_size_arr[2] = {0, (GLint)0xdeadc0de};
    glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, buffer_size_arr);
    GLint buffer_size = buffer_size_arr[0];
    assert(buffer_size_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_SIZE");
    writer.writeInt(buffer_size);
                writer.endMember();
            }
        }

        // GL_BUFFER_USAGE
        {
            flushErrors();
    GLint buffer_usage_arr[2] = {0, (GLint)0xdeadc0de};
    glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_USAGE, buffer_usage_arr);
    GLint buffer_usage = buffer_usage_arr[0];
    assert(buffer_usage_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_USAGE");
    dumpEnum(writer, buffer_usage);
                writer.endMember();
            }
        }



        // GL_BUFFER_MAPPED
        {
            flushErrors();
    GLint buffer_mapped_arr[2] = {0, (GLint)0xdeadc0de};
    glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_MAPPED, buffer_mapped_arr);
    GLint buffer_mapped = buffer_mapped_arr[0];
    assert(buffer_mapped_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_MAPPED");
    dumpBoolean(writer, buffer_mapped);
                writer.endMember();
            }
        }

        // GL_BUFFER_MAP_POINTER
        {
            flushErrors();
    GLvoid *buffer_map_pointer;
    glGetBufferPointerv(GL_ARRAY_BUFFER, GL_BUFFER_MAP_POINTER, &buffer_map_pointer);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_MAP_POINTER");
    writer.writeInt((size_t)buffer_map_pointer);
                writer.endMember();
            }
        }

        // GL_BUFFER_ACCESS_FLAGS
        {
            flushErrors();
    GLint buffer_access_flags_arr[2] = {0, (GLint)0xdeadc0de};
    glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_ACCESS_FLAGS, buffer_access_flags_arr);
    GLint buffer_access_flags = buffer_access_flags_arr[0];
    assert(buffer_access_flags_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_ACCESS_FLAGS");
    writer.writeInt(buffer_access_flags);
                writer.endMember();
            }
        }

        // GL_BUFFER_MAP_LENGTH
        {
            flushErrors();
    GLint buffer_map_length_arr[2] = {0, (GLint)0xdeadc0de};
    glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_MAP_LENGTH, buffer_map_length_arr);
    GLint buffer_map_length = buffer_map_length_arr[0];
    assert(buffer_map_length_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_MAP_LENGTH");
    writer.writeInt(buffer_map_length);
                writer.endMember();
            }
        }

        // GL_BUFFER_MAP_OFFSET
        {
            flushErrors();
    GLint buffer_map_offset_arr[2] = {0, (GLint)0xdeadc0de};
    glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_MAP_OFFSET, buffer_map_offset_arr);
    GLint buffer_map_offset = buffer_map_offset_arr[0];
    assert(buffer_map_offset_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_MAP_OFFSET");
    writer.writeInt(buffer_map_offset);
                writer.endMember();
            }
        }

        }
        writer.endObject();
        writer.endMember();
    }

    // GL_COPY_READ_BUFFER
    {
        writer.beginMember("GL_COPY_READ_BUFFER");
        writer.beginObject();
        GLint buffer = 0;
        glGetIntegerv(GL_COPY_READ_BUFFER_BINDING, &buffer);
        if (buffer) {


        // GL_BUFFER_SIZE
        {
            flushErrors();
    GLint buffer_size_arr[2] = {0, (GLint)0xdeadc0de};
    glGetBufferParameteriv(GL_COPY_READ_BUFFER, GL_BUFFER_SIZE, buffer_size_arr);
    GLint buffer_size = buffer_size_arr[0];
    assert(buffer_size_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_SIZE");
    writer.writeInt(buffer_size);
                writer.endMember();
            }
        }

        // GL_BUFFER_USAGE
        {
            flushErrors();
    GLint buffer_usage_arr[2] = {0, (GLint)0xdeadc0de};
    glGetBufferParameteriv(GL_COPY_READ_BUFFER, GL_BUFFER_USAGE, buffer_usage_arr);
    GLint buffer_usage = buffer_usage_arr[0];
    assert(buffer_usage_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_USAGE");
    dumpEnum(writer, buffer_usage);
                writer.endMember();
            }
        }



        // GL_BUFFER_MAPPED
        {
            flushErrors();
    GLint buffer_mapped_arr[2] = {0, (GLint)0xdeadc0de};
    glGetBufferParameteriv(GL_COPY_READ_BUFFER, GL_BUFFER_MAPPED, buffer_mapped_arr);
    GLint buffer_mapped = buffer_mapped_arr[0];
    assert(buffer_mapped_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_MAPPED");
    dumpBoolean(writer, buffer_mapped);
                writer.endMember();
            }
        }

        // GL_BUFFER_MAP_POINTER
        {
            flushErrors();
    GLvoid *buffer_map_pointer;
    glGetBufferPointerv(GL_COPY_READ_BUFFER, GL_BUFFER_MAP_POINTER, &buffer_map_pointer);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_MAP_POINTER");
    writer.writeInt((size_t)buffer_map_pointer);
                writer.endMember();
            }
        }

        // GL_BUFFER_ACCESS_FLAGS
        {
            flushErrors();
    GLint buffer_access_flags_arr[2] = {0, (GLint)0xdeadc0de};
    glGetBufferParameteriv(GL_COPY_READ_BUFFER, GL_BUFFER_ACCESS_FLAGS, buffer_access_flags_arr);
    GLint buffer_access_flags = buffer_access_flags_arr[0];
    assert(buffer_access_flags_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_ACCESS_FLAGS");
    writer.writeInt(buffer_access_flags);
                writer.endMember();
            }
        }

        // GL_BUFFER_MAP_LENGTH
        {
            flushErrors();
    GLint buffer_map_length_arr[2] = {0, (GLint)0xdeadc0de};
    glGetBufferParameteriv(GL_COPY_READ_BUFFER, GL_BUFFER_MAP_LENGTH, buffer_map_length_arr);
    GLint buffer_map_length = buffer_map_length_arr[0];
    assert(buffer_map_length_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_MAP_LENGTH");
    writer.writeInt(buffer_map_length);
                writer.endMember();
            }
        }

        // GL_BUFFER_MAP_OFFSET
        {
            flushErrors();
    GLint buffer_map_offset_arr[2] = {0, (GLint)0xdeadc0de};
    glGetBufferParameteriv(GL_COPY_READ_BUFFER, GL_BUFFER_MAP_OFFSET, buffer_map_offset_arr);
    GLint buffer_map_offset = buffer_map_offset_arr[0];
    assert(buffer_map_offset_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_MAP_OFFSET");
    writer.writeInt(buffer_map_offset);
                writer.endMember();
            }
        }

        }
        writer.endObject();
        writer.endMember();
    }

    // GL_COPY_WRITE_BUFFER
    {
        writer.beginMember("GL_COPY_WRITE_BUFFER");
        writer.beginObject();
        GLint buffer = 0;
        glGetIntegerv(GL_COPY_WRITE_BUFFER_BINDING, &buffer);
        if (buffer) {

        // GL_BUFFER_SIZE
        {
            flushErrors();
    GLint buffer_size_arr[2] = {0, (GLint)0xdeadc0de};
    glGetBufferParameteriv(GL_COPY_WRITE_BUFFER, GL_BUFFER_SIZE, buffer_size_arr);
    GLint buffer_size = buffer_size_arr[0];
    assert(buffer_size_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_SIZE");
    writer.writeInt(buffer_size);
                writer.endMember();
            }
        }

        // GL_BUFFER_USAGE
        {
            flushErrors();
    GLint buffer_usage_arr[2] = {0, (GLint)0xdeadc0de};
    glGetBufferParameteriv(GL_COPY_WRITE_BUFFER, GL_BUFFER_USAGE, buffer_usage_arr);
    GLint buffer_usage = buffer_usage_arr[0];
    assert(buffer_usage_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_USAGE");
    dumpEnum(writer, buffer_usage);
                writer.endMember();
            }
        }



        // GL_BUFFER_MAPPED
        {
            flushErrors();
    GLint buffer_mapped_arr[2] = {0, (GLint)0xdeadc0de};
    glGetBufferParameteriv(GL_COPY_WRITE_BUFFER, GL_BUFFER_MAPPED, buffer_mapped_arr);
    GLint buffer_mapped = buffer_mapped_arr[0];
    assert(buffer_mapped_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_MAPPED");
    dumpBoolean(writer, buffer_mapped);
                writer.endMember();
            }
        }

        // GL_BUFFER_MAP_POINTER
        {
            flushErrors();
    GLvoid *buffer_map_pointer;
    glGetBufferPointerv(GL_COPY_WRITE_BUFFER, GL_BUFFER_MAP_POINTER, &buffer_map_pointer);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_MAP_POINTER");
    writer.writeInt((size_t)buffer_map_pointer);
                writer.endMember();
            }
        }

        // GL_BUFFER_ACCESS_FLAGS
        {
            flushErrors();
    GLint buffer_access_flags_arr[2] = {0, (GLint)0xdeadc0de};
    glGetBufferParameteriv(GL_COPY_WRITE_BUFFER, GL_BUFFER_ACCESS_FLAGS, buffer_access_flags_arr);
    GLint buffer_access_flags = buffer_access_flags_arr[0];
    assert(buffer_access_flags_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_ACCESS_FLAGS");
    writer.writeInt(buffer_access_flags);
                writer.endMember();
            }
        }

        // GL_BUFFER_MAP_LENGTH
        {
            flushErrors();
    GLint buffer_map_length_arr[2] = {0, (GLint)0xdeadc0de};
    glGetBufferParameteriv(GL_COPY_WRITE_BUFFER, GL_BUFFER_MAP_LENGTH, buffer_map_length_arr);
    GLint buffer_map_length = buffer_map_length_arr[0];
    assert(buffer_map_length_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_MAP_LENGTH");
    writer.writeInt(buffer_map_length);
                writer.endMember();
            }
        }

        // GL_BUFFER_MAP_OFFSET
        {
            flushErrors();
    GLint buffer_map_offset_arr[2] = {0, (GLint)0xdeadc0de};
    glGetBufferParameteriv(GL_COPY_WRITE_BUFFER, GL_BUFFER_MAP_OFFSET, buffer_map_offset_arr);
    GLint buffer_map_offset = buffer_map_offset_arr[0];
    assert(buffer_map_offset_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_MAP_OFFSET");
    writer.writeInt(buffer_map_offset);
                writer.endMember();
            }
        }

        }
        writer.endObject();
        writer.endMember();
    }

    // GL_ELEMENT_ARRAY_BUFFER
    {
        writer.beginMember("GL_ELEMENT_ARRAY_BUFFER");
        writer.beginObject();
        GLint buffer = 0;
        glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &buffer);
        if (buffer) {


        // GL_BUFFER_SIZE
        {
            flushErrors();
    GLint buffer_size_arr[2] = {0, (GLint)0xdeadc0de};
    glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, buffer_size_arr);
    GLint buffer_size = buffer_size_arr[0];
    assert(buffer_size_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_SIZE");
    writer.writeInt(buffer_size);
                writer.endMember();
            }
        }

        // GL_BUFFER_USAGE
        {
            flushErrors();
    GLint buffer_usage_arr[2] = {0, (GLint)0xdeadc0de};
    glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_USAGE, buffer_usage_arr);
    GLint buffer_usage = buffer_usage_arr[0];
    assert(buffer_usage_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_USAGE");
    dumpEnum(writer, buffer_usage);
                writer.endMember();
            }
        }


        // GL_BUFFER_MAPPED
        {
            flushErrors();
    GLint buffer_mapped_arr[2] = {0, (GLint)0xdeadc0de};
    glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_MAPPED, buffer_mapped_arr);
    GLint buffer_mapped = buffer_mapped_arr[0];
    assert(buffer_mapped_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_MAPPED");
    dumpBoolean(writer, buffer_mapped);
                writer.endMember();
            }
        }

        // GL_BUFFER_MAP_POINTER
        {
            flushErrors();
    GLvoid *buffer_map_pointer;
    glGetBufferPointerv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_MAP_POINTER, &buffer_map_pointer);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_MAP_POINTER");
    writer.writeInt((size_t)buffer_map_pointer);
                writer.endMember();
            }
        }

        // GL_BUFFER_ACCESS_FLAGS
        {
            flushErrors();
    GLint buffer_access_flags_arr[2] = {0, (GLint)0xdeadc0de};
    glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_ACCESS_FLAGS, buffer_access_flags_arr);
    GLint buffer_access_flags = buffer_access_flags_arr[0];
    assert(buffer_access_flags_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_ACCESS_FLAGS");
    writer.writeInt(buffer_access_flags);
                writer.endMember();
            }
        }

        // GL_BUFFER_MAP_LENGTH
        {
            flushErrors();
    GLint buffer_map_length_arr[2] = {0, (GLint)0xdeadc0de};
    glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_MAP_LENGTH, buffer_map_length_arr);
    GLint buffer_map_length = buffer_map_length_arr[0];
    assert(buffer_map_length_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_MAP_LENGTH");
    writer.writeInt(buffer_map_length);
                writer.endMember();
            }
        }

        // GL_BUFFER_MAP_OFFSET
        {
            flushErrors();
    GLint buffer_map_offset_arr[2] = {0, (GLint)0xdeadc0de};
    glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_MAP_OFFSET, buffer_map_offset_arr);
    GLint buffer_map_offset = buffer_map_offset_arr[0];
    assert(buffer_map_offset_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_MAP_OFFSET");
    writer.writeInt(buffer_map_offset);
                writer.endMember();
            }
        }

        }
        writer.endObject();
        writer.endMember();
    }

    // GL_PIXEL_PACK_BUFFER
    {
        writer.beginMember("GL_PIXEL_PACK_BUFFER");
        writer.beginObject();
        GLint buffer = 0;
        glGetIntegerv(GL_PIXEL_PACK_BUFFER_BINDING, &buffer);
        if (buffer) {


        // GL_BUFFER_SIZE
        {
            flushErrors();
    GLint buffer_size_arr[2] = {0, (GLint)0xdeadc0de};
    glGetBufferParameteriv(GL_PIXEL_PACK_BUFFER, GL_BUFFER_SIZE, buffer_size_arr);
    GLint buffer_size = buffer_size_arr[0];
    assert(buffer_size_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_SIZE");
    writer.writeInt(buffer_size);
                writer.endMember();
            }
        }

        // GL_BUFFER_USAGE
        {
            flushErrors();
    GLint buffer_usage_arr[2] = {0, (GLint)0xdeadc0de};
    glGetBufferParameteriv(GL_PIXEL_PACK_BUFFER, GL_BUFFER_USAGE, buffer_usage_arr);
    GLint buffer_usage = buffer_usage_arr[0];
    assert(buffer_usage_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_USAGE");
    dumpEnum(writer, buffer_usage);
                writer.endMember();
            }
        }


        // GL_BUFFER_MAPPED
        {
            flushErrors();
    GLint buffer_mapped_arr[2] = {0, (GLint)0xdeadc0de};
    glGetBufferParameteriv(GL_PIXEL_PACK_BUFFER, GL_BUFFER_MAPPED, buffer_mapped_arr);
    GLint buffer_mapped = buffer_mapped_arr[0];
    assert(buffer_mapped_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_MAPPED");
    dumpBoolean(writer, buffer_mapped);
                writer.endMember();
            }
        }

        // GL_BUFFER_MAP_POINTER
        {
            flushErrors();
    GLvoid *buffer_map_pointer;
    glGetBufferPointerv(GL_PIXEL_PACK_BUFFER, GL_BUFFER_MAP_POINTER, &buffer_map_pointer);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_MAP_POINTER");
    writer.writeInt((size_t)buffer_map_pointer);
                writer.endMember();
            }
        }

        // GL_BUFFER_ACCESS_FLAGS
        {
            flushErrors();
    GLint buffer_access_flags_arr[2] = {0, (GLint)0xdeadc0de};
    glGetBufferParameteriv(GL_PIXEL_PACK_BUFFER, GL_BUFFER_ACCESS_FLAGS, buffer_access_flags_arr);
    GLint buffer_access_flags = buffer_access_flags_arr[0];
    assert(buffer_access_flags_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_ACCESS_FLAGS");
    writer.writeInt(buffer_access_flags);
                writer.endMember();
            }
        }

        // GL_BUFFER_MAP_LENGTH
        {
            flushErrors();
    GLint buffer_map_length_arr[2] = {0, (GLint)0xdeadc0de};
    glGetBufferParameteriv(GL_PIXEL_PACK_BUFFER, GL_BUFFER_MAP_LENGTH, buffer_map_length_arr);
    GLint buffer_map_length = buffer_map_length_arr[0];
    assert(buffer_map_length_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_MAP_LENGTH");
    writer.writeInt(buffer_map_length);
                writer.endMember();
            }
        }

        // GL_BUFFER_MAP_OFFSET
        {
            flushErrors();
    GLint buffer_map_offset_arr[2] = {0, (GLint)0xdeadc0de};
    glGetBufferParameteriv(GL_PIXEL_PACK_BUFFER, GL_BUFFER_MAP_OFFSET, buffer_map_offset_arr);
    GLint buffer_map_offset = buffer_map_offset_arr[0];
    assert(buffer_map_offset_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_MAP_OFFSET");
    writer.writeInt(buffer_map_offset);
                writer.endMember();
            }
        }

        }
        writer.endObject();
        writer.endMember();
    }

    // GL_PIXEL_UNPACK_BUFFER
    {
        writer.beginMember("GL_PIXEL_UNPACK_BUFFER");
        writer.beginObject();
        GLint buffer = 0;
        glGetIntegerv(GL_PIXEL_UNPACK_BUFFER_BINDING, &buffer);
        if (buffer) {


        // GL_BUFFER_SIZE
        {
            flushErrors();
    GLint buffer_size_arr[2] = {0, (GLint)0xdeadc0de};
    glGetBufferParameteriv(GL_PIXEL_UNPACK_BUFFER, GL_BUFFER_SIZE, buffer_size_arr);
    GLint buffer_size = buffer_size_arr[0];
    assert(buffer_size_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_SIZE");
    writer.writeInt(buffer_size);
                writer.endMember();
            }
        }

        // GL_BUFFER_USAGE
        {
            flushErrors();
    GLint buffer_usage_arr[2] = {0, (GLint)0xdeadc0de};
    glGetBufferParameteriv(GL_PIXEL_UNPACK_BUFFER, GL_BUFFER_USAGE, buffer_usage_arr);
    GLint buffer_usage = buffer_usage_arr[0];
    assert(buffer_usage_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_USAGE");
    dumpEnum(writer, buffer_usage);
                writer.endMember();
            }
        }



        // GL_BUFFER_MAPPED
        {
            flushErrors();
    GLint buffer_mapped_arr[2] = {0, (GLint)0xdeadc0de};
    glGetBufferParameteriv(GL_PIXEL_UNPACK_BUFFER, GL_BUFFER_MAPPED, buffer_mapped_arr);
    GLint buffer_mapped = buffer_mapped_arr[0];
    assert(buffer_mapped_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_MAPPED");
    dumpBoolean(writer, buffer_mapped);
                writer.endMember();
            }
        }

        // GL_BUFFER_MAP_POINTER
        {
            flushErrors();
    GLvoid *buffer_map_pointer;
    glGetBufferPointerv(GL_PIXEL_UNPACK_BUFFER, GL_BUFFER_MAP_POINTER, &buffer_map_pointer);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_MAP_POINTER");
    writer.writeInt((size_t)buffer_map_pointer);
                writer.endMember();
            }
        }

        // GL_BUFFER_ACCESS_FLAGS
        {
            flushErrors();
    GLint buffer_access_flags_arr[2] = {0, (GLint)0xdeadc0de};
    glGetBufferParameteriv(GL_PIXEL_UNPACK_BUFFER, GL_BUFFER_ACCESS_FLAGS, buffer_access_flags_arr);
    GLint buffer_access_flags = buffer_access_flags_arr[0];
    assert(buffer_access_flags_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_ACCESS_FLAGS");
    writer.writeInt(buffer_access_flags);
                writer.endMember();
            }
        }

        // GL_BUFFER_MAP_LENGTH
        {
            flushErrors();
    GLint buffer_map_length_arr[2] = {0, (GLint)0xdeadc0de};
    glGetBufferParameteriv(GL_PIXEL_UNPACK_BUFFER, GL_BUFFER_MAP_LENGTH, buffer_map_length_arr);
    GLint buffer_map_length = buffer_map_length_arr[0];
    assert(buffer_map_length_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_MAP_LENGTH");
    writer.writeInt(buffer_map_length);
                writer.endMember();
            }
        }

        // GL_BUFFER_MAP_OFFSET
        {
            flushErrors();
    GLint buffer_map_offset_arr[2] = {0, (GLint)0xdeadc0de};
    glGetBufferParameteriv(GL_PIXEL_UNPACK_BUFFER, GL_BUFFER_MAP_OFFSET, buffer_map_offset_arr);
    GLint buffer_map_offset = buffer_map_offset_arr[0];
    assert(buffer_map_offset_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_MAP_OFFSET");
    writer.writeInt(buffer_map_offset);
                writer.endMember();
            }
        }

        }
        writer.endObject();
        writer.endMember();
    }



    // GL_TRANSFORM_FEEDBACK_BUFFER
    {
        writer.beginMember("GL_TRANSFORM_FEEDBACK_BUFFER");
        writer.beginObject();
        GLint buffer = 0;
        glGetIntegerv(GL_TRANSFORM_FEEDBACK_BUFFER_BINDING, &buffer);
        if (buffer) {


        // GL_BUFFER_SIZE
        {
            flushErrors();
    GLint buffer_size_arr[2] = {0, (GLint)0xdeadc0de};
    glGetBufferParameteriv(GL_TRANSFORM_FEEDBACK_BUFFER, GL_BUFFER_SIZE, buffer_size_arr);
    GLint buffer_size = buffer_size_arr[0];
    assert(buffer_size_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_SIZE");
    writer.writeInt(buffer_size);
                writer.endMember();
            }
        }

        // GL_BUFFER_USAGE
        {
            flushErrors();
    GLint buffer_usage_arr[2] = {0, (GLint)0xdeadc0de};
    glGetBufferParameteriv(GL_TRANSFORM_FEEDBACK_BUFFER, GL_BUFFER_USAGE, buffer_usage_arr);
    GLint buffer_usage = buffer_usage_arr[0];
    assert(buffer_usage_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_USAGE");
    dumpEnum(writer, buffer_usage);
                writer.endMember();
            }
        }

        // GL_BUFFER_MAPPED
        {
            flushErrors();
    GLint buffer_mapped_arr[2] = {0, (GLint)0xdeadc0de};
    glGetBufferParameteriv(GL_TRANSFORM_FEEDBACK_BUFFER, GL_BUFFER_MAPPED, buffer_mapped_arr);
    GLint buffer_mapped = buffer_mapped_arr[0];
    assert(buffer_mapped_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_MAPPED");
    dumpBoolean(writer, buffer_mapped);
                writer.endMember();
            }
        }

        // GL_BUFFER_MAP_POINTER
        {
            flushErrors();
    GLvoid *buffer_map_pointer;
    glGetBufferPointerv(GL_TRANSFORM_FEEDBACK_BUFFER, GL_BUFFER_MAP_POINTER, &buffer_map_pointer);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_MAP_POINTER");
    writer.writeInt((size_t)buffer_map_pointer);
                writer.endMember();
            }
        }

        // GL_BUFFER_ACCESS_FLAGS
        {
            flushErrors();
    GLint buffer_access_flags_arr[2] = {0, (GLint)0xdeadc0de};
    glGetBufferParameteriv(GL_TRANSFORM_FEEDBACK_BUFFER, GL_BUFFER_ACCESS_FLAGS, buffer_access_flags_arr);
    GLint buffer_access_flags = buffer_access_flags_arr[0];
    assert(buffer_access_flags_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_ACCESS_FLAGS");
    writer.writeInt(buffer_access_flags);
                writer.endMember();
            }
        }

        // GL_BUFFER_MAP_LENGTH
        {
            flushErrors();
    GLint buffer_map_length_arr[2] = {0, (GLint)0xdeadc0de};
    glGetBufferParameteriv(GL_TRANSFORM_FEEDBACK_BUFFER, GL_BUFFER_MAP_LENGTH, buffer_map_length_arr);
    GLint buffer_map_length = buffer_map_length_arr[0];
    assert(buffer_map_length_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_MAP_LENGTH");
    writer.writeInt(buffer_map_length);
                writer.endMember();
            }
        }

        // GL_BUFFER_MAP_OFFSET
        {
            flushErrors();
    GLint buffer_map_offset_arr[2] = {0, (GLint)0xdeadc0de};
    glGetBufferParameteriv(GL_TRANSFORM_FEEDBACK_BUFFER, GL_BUFFER_MAP_OFFSET, buffer_map_offset_arr);
    GLint buffer_map_offset = buffer_map_offset_arr[0];
    assert(buffer_map_offset_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_MAP_OFFSET");
    writer.writeInt(buffer_map_offset);
                writer.endMember();
            }
        }

        }
        GLint max_bindings = 0;
        glGetIntegerv(GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS, &max_bindings);
        if (max_bindings) {
            writer.beginMember("i");
            writer.beginArray();
            for (GLint i = 0; i < max_bindings; ++i) {
                writer.beginObject();
        // GL_TRANSFORM_FEEDBACK_BUFFER_BINDING
        {
            flushErrors();
    GLint transform_feedback_buffer_binding_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegeri_v(GL_TRANSFORM_FEEDBACK_BUFFER_BINDING, i, transform_feedback_buffer_binding_arr);
    GLint transform_feedback_buffer_binding = transform_feedback_buffer_binding_arr[0];
    assert(transform_feedback_buffer_binding_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_TRANSFORM_FEEDBACK_BUFFER_BINDING");
    writer.writeInt(transform_feedback_buffer_binding);
                writer.endMember();
            }
        }

        // GL_TRANSFORM_FEEDBACK_BUFFER_START
        {
            flushErrors();
    GLint transform_feedback_buffer_start_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegeri_v(GL_TRANSFORM_FEEDBACK_BUFFER_START, i, transform_feedback_buffer_start_arr);
    GLint transform_feedback_buffer_start = transform_feedback_buffer_start_arr[0];
    assert(transform_feedback_buffer_start_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_TRANSFORM_FEEDBACK_BUFFER_START");
    writer.writeInt(transform_feedback_buffer_start);
                writer.endMember();
            }
        }

        // GL_TRANSFORM_FEEDBACK_BUFFER_SIZE
        {
            flushErrors();
    GLint transform_feedback_buffer_size_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegeri_v(GL_TRANSFORM_FEEDBACK_BUFFER_SIZE, i, transform_feedback_buffer_size_arr);
    GLint transform_feedback_buffer_size = transform_feedback_buffer_size_arr[0];
    assert(transform_feedback_buffer_size_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_TRANSFORM_FEEDBACK_BUFFER_SIZE");
    writer.writeInt(transform_feedback_buffer_size);
                writer.endMember();
            }
        }

                writer.endObject();
            }
            writer.endArray();
            writer.endMember();
        }
        writer.endObject();
        writer.endMember();
    }

    // GL_UNIFORM_BUFFER
    {
        writer.beginMember("GL_UNIFORM_BUFFER");
        writer.beginObject();
        GLint buffer = 0;
        glGetIntegerv(GL_UNIFORM_BUFFER_BINDING, &buffer);
        if (buffer) {


        // GL_BUFFER_SIZE
        {
            flushErrors();
    GLint buffer_size_arr[2] = {0, (GLint)0xdeadc0de};
    glGetBufferParameteriv(GL_UNIFORM_BUFFER, GL_BUFFER_SIZE, buffer_size_arr);
    GLint buffer_size = buffer_size_arr[0];
    assert(buffer_size_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_SIZE");
    writer.writeInt(buffer_size);
                writer.endMember();
            }
        }

        // GL_BUFFER_USAGE
        {
            flushErrors();
    GLint buffer_usage_arr[2] = {0, (GLint)0xdeadc0de};
    glGetBufferParameteriv(GL_UNIFORM_BUFFER, GL_BUFFER_USAGE, buffer_usage_arr);
    GLint buffer_usage = buffer_usage_arr[0];
    assert(buffer_usage_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_USAGE");
    dumpEnum(writer, buffer_usage);
                writer.endMember();
            }
        }



        // GL_BUFFER_MAPPED
        {
            flushErrors();
    GLint buffer_mapped_arr[2] = {0, (GLint)0xdeadc0de};
    glGetBufferParameteriv(GL_UNIFORM_BUFFER, GL_BUFFER_MAPPED, buffer_mapped_arr);
    GLint buffer_mapped = buffer_mapped_arr[0];
    assert(buffer_mapped_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_MAPPED");
    dumpBoolean(writer, buffer_mapped);
                writer.endMember();
            }
        }

        // GL_BUFFER_MAP_POINTER
        {
            flushErrors();
    GLvoid *buffer_map_pointer;
    glGetBufferPointerv(GL_UNIFORM_BUFFER, GL_BUFFER_MAP_POINTER, &buffer_map_pointer);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_MAP_POINTER");
    writer.writeInt((size_t)buffer_map_pointer);
                writer.endMember();
            }
        }

        // GL_BUFFER_ACCESS_FLAGS
        {
            flushErrors();
    GLint buffer_access_flags_arr[2] = {0, (GLint)0xdeadc0de};
    glGetBufferParameteriv(GL_UNIFORM_BUFFER, GL_BUFFER_ACCESS_FLAGS, buffer_access_flags_arr);
    GLint buffer_access_flags = buffer_access_flags_arr[0];
    assert(buffer_access_flags_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_ACCESS_FLAGS");
    writer.writeInt(buffer_access_flags);
                writer.endMember();
            }
        }

        // GL_BUFFER_MAP_LENGTH
        {
            flushErrors();
    GLint buffer_map_length_arr[2] = {0, (GLint)0xdeadc0de};
    glGetBufferParameteriv(GL_UNIFORM_BUFFER, GL_BUFFER_MAP_LENGTH, buffer_map_length_arr);
    GLint buffer_map_length = buffer_map_length_arr[0];
    assert(buffer_map_length_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_MAP_LENGTH");
    writer.writeInt(buffer_map_length);
                writer.endMember();
            }
        }

        // GL_BUFFER_MAP_OFFSET
        {
            flushErrors();
    GLint buffer_map_offset_arr[2] = {0, (GLint)0xdeadc0de};
    glGetBufferParameteriv(GL_UNIFORM_BUFFER, GL_BUFFER_MAP_OFFSET, buffer_map_offset_arr);
    GLint buffer_map_offset = buffer_map_offset_arr[0];
    assert(buffer_map_offset_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_BUFFER_MAP_OFFSET");
    writer.writeInt(buffer_map_offset);
                writer.endMember();
            }
        }

        }
        GLint max_bindings = 0;
        glGetIntegerv(GL_MAX_UNIFORM_BUFFER_BINDINGS, &max_bindings);
        if (max_bindings) {
            writer.beginMember("i");
            writer.beginArray();
            for (GLint i = 0; i < max_bindings; ++i) {
                writer.beginObject();
        // GL_UNIFORM_BUFFER_BINDING
        {
            flushErrors();
    GLint uniform_buffer_binding_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegeri_v(GL_UNIFORM_BUFFER_BINDING, i, uniform_buffer_binding_arr);
    GLint uniform_buffer_binding = uniform_buffer_binding_arr[0];
    assert(uniform_buffer_binding_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_UNIFORM_BUFFER_BINDING");
    writer.writeInt(uniform_buffer_binding);
                writer.endMember();
            }
        }

        // GL_UNIFORM_BUFFER_START
        {
            flushErrors();
    GLint uniform_buffer_start_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegeri_v(GL_UNIFORM_BUFFER_START, i, uniform_buffer_start_arr);
    GLint uniform_buffer_start = uniform_buffer_start_arr[0];
    assert(uniform_buffer_start_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_UNIFORM_BUFFER_START");
    writer.writeInt(uniform_buffer_start);
                writer.endMember();
            }
        }

        // GL_UNIFORM_BUFFER_SIZE
        {
            flushErrors();
    GLint uniform_buffer_size_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegeri_v(GL_UNIFORM_BUFFER_SIZE, i, uniform_buffer_size_arr);
    GLint uniform_buffer_size = uniform_buffer_size_arr[0];
    assert(uniform_buffer_size_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_UNIFORM_BUFFER_SIZE");
    writer.writeInt(uniform_buffer_size);
                writer.endMember();
            }
        }

                writer.endObject();
            }
            writer.endArray();
            writer.endMember();
        }
        writer.endObject();
        writer.endMember();
    }

    {
        GLint active_texture = GL_TEXTURE0;
        glGetIntegerv(GL_ACTIVE_TEXTURE, &active_texture);
        GLint max_texture_coords = 0;
        GLint max_combined_texture_image_units = 0;
        glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &max_combined_texture_image_units);
        max_combined_texture_image_units = std::max(max_combined_texture_image_units, 2);
        GLint max_units = std::max(max_combined_texture_image_units, max_texture_coords);
        for (GLint unit = 0; unit < max_units; ++unit) {
            std::string name = std::string("GL_TEXTURE") + std::to_string(unit);
            writer.beginMember(name);
            glActiveTexture(GL_TEXTURE0 + unit);
            writer.beginObject();


        // GL_TEXTURE_BINDING_2D
        {
            flushErrors();
    GLint texture_binding_2d_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_TEXTURE_BINDING_2D, texture_binding_2d_arr);
    GLint texture_binding_2d = texture_binding_2d_arr[0];
    assert(texture_binding_2d_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_TEXTURE_BINDING_2D");
    writer.writeInt(texture_binding_2d);
                writer.endMember();
            }
        }

        // GL_TEXTURE_BINDING_3D
        {
            flushErrors();
    GLint texture_binding_3d_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_TEXTURE_BINDING_3D, texture_binding_3d_arr);
    GLint texture_binding_3d = texture_binding_3d_arr[0];
    assert(texture_binding_3d_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_TEXTURE_BINDING_3D");
    writer.writeInt(texture_binding_3d);
                writer.endMember();
            }
        }


        // GL_TEXTURE_BINDING_CUBE_MAP
        {
            flushErrors();
    GLint texture_binding_cube_map_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_TEXTURE_BINDING_CUBE_MAP, texture_binding_cube_map_arr);
    GLint texture_binding_cube_map = texture_binding_cube_map_arr[0];
    assert(texture_binding_cube_map_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_TEXTURE_BINDING_CUBE_MAP");
    writer.writeInt(texture_binding_cube_map);
                writer.endMember();
            }
        }



        // GL_TEXTURE_BINDING_2D_ARRAY
        {
            flushErrors();
    GLint texture_binding_2d_array_arr[2] = {0, (GLint)0xdeadc0de};
    glGetIntegerv(GL_TEXTURE_BINDING_2D_ARRAY, texture_binding_2d_array_arr);
    GLint texture_binding_2d_array = texture_binding_2d_array_arr[0];
    assert(texture_binding_2d_array_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_TEXTURE_BINDING_2D_ARRAY");
    writer.writeInt(texture_binding_2d_array);
                writer.endMember();
            }
        }




            for (unsigned i = 0; i < numTextureTargets; ++i) {
                GLenum target = textureTargets[i];
                GLboolean enabled = GL_FALSE;
                if (unit < max_texture_coords &&
                    (target == GL_TEXTURE_2D ||
                     target == GL_TEXTURE_3D ||
                     target == GL_TEXTURE_CUBE_MAP)) {
                    glGetBooleanv(target, &enabled);
                    writer.beginMember(enumToString(target));
                    dumpBoolean(writer, enabled);
                    writer.endMember();
                }
                GLint texture = 0;
                GLenum binding = getTextureBinding(target);
                glGetIntegerv(binding, &texture);
                if (enabled || texture) {
                    dumpTextureTargetParameters(writer, context, target, texture);
                }
            }

    // GL_SAMPLER_BINDING
    if (true) {
        GLint sampler_binding = 0;
        glGetIntegerv(GL_SAMPLER_BINDING, &sampler_binding);
        writer.beginMember("GL_SAMPLER_BINDING");
        writer.writeInt(sampler_binding);
        writer.endMember();
        if (sampler_binding) {
            writer.beginMember("GL_SAMPLER");
            writer.beginObject();


        // GL_TEXTURE_MAG_FILTER
        {
            flushErrors();
    GLint texture_mag_filter_arr[2] = {0, (GLint)0xdeadc0de};
    glGetSamplerParameteriv(sampler_binding, GL_TEXTURE_MAG_FILTER, texture_mag_filter_arr);
    GLint texture_mag_filter = texture_mag_filter_arr[0];
    assert(texture_mag_filter_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_TEXTURE_MAG_FILTER");
    dumpEnum(writer, texture_mag_filter);
                writer.endMember();
            }
        }

        // GL_TEXTURE_MIN_FILTER
        {
            flushErrors();
    GLint texture_min_filter_arr[2] = {0, (GLint)0xdeadc0de};
    glGetSamplerParameteriv(sampler_binding, GL_TEXTURE_MIN_FILTER, texture_min_filter_arr);
    GLint texture_min_filter = texture_min_filter_arr[0];
    assert(texture_min_filter_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_TEXTURE_MIN_FILTER");
    dumpEnum(writer, texture_min_filter);
                writer.endMember();
            }
        }

        // GL_TEXTURE_WRAP_S
        {
            flushErrors();
    GLint texture_wrap_s_arr[2] = {0, (GLint)0xdeadc0de};
    glGetSamplerParameteriv(sampler_binding, GL_TEXTURE_WRAP_S, texture_wrap_s_arr);
    GLint texture_wrap_s = texture_wrap_s_arr[0];
    assert(texture_wrap_s_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_TEXTURE_WRAP_S");
    dumpEnum(writer, texture_wrap_s);
                writer.endMember();
            }
        }

        // GL_TEXTURE_WRAP_T
        {
            flushErrors();
    GLint texture_wrap_t_arr[2] = {0, (GLint)0xdeadc0de};
    glGetSamplerParameteriv(sampler_binding, GL_TEXTURE_WRAP_T, texture_wrap_t_arr);
    GLint texture_wrap_t = texture_wrap_t_arr[0];
    assert(texture_wrap_t_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_TEXTURE_WRAP_T");
    dumpEnum(writer, texture_wrap_t);
                writer.endMember();
            }
        }

        // GL_TEXTURE_WRAP_R
        {
            flushErrors();
    GLint texture_wrap_r_arr[2] = {0, (GLint)0xdeadc0de};
    glGetSamplerParameteriv(sampler_binding, GL_TEXTURE_WRAP_R, texture_wrap_r_arr);
    GLint texture_wrap_r = texture_wrap_r_arr[0];
    assert(texture_wrap_r_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_TEXTURE_WRAP_R");
    dumpEnum(writer, texture_wrap_r);
                writer.endMember();
            }
        }

        // GL_TEXTURE_MIN_LOD
        {
            flushErrors();
    GLfloat texture_min_lod_arr[2] = {0, (GLfloat)0xdeadc0de};
    glGetSamplerParameterfv(sampler_binding, GL_TEXTURE_MIN_LOD, texture_min_lod_arr);
    GLfloat texture_min_lod = texture_min_lod_arr[0];
    assert(texture_min_lod_arr[1] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_TEXTURE_MIN_LOD");
    writer.writeFloat(texture_min_lod);
                writer.endMember();
            }
        }

        // GL_TEXTURE_MAX_LOD
        {
            flushErrors();
    GLfloat texture_max_lod_arr[2] = {0, (GLfloat)0xdeadc0de};
    glGetSamplerParameterfv(sampler_binding, GL_TEXTURE_MAX_LOD, texture_max_lod_arr);
    GLfloat texture_max_lod = texture_max_lod_arr[0];
    assert(texture_max_lod_arr[1] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_TEXTURE_MAX_LOD");
    writer.writeFloat(texture_max_lod);
                writer.endMember();
            }
        }

        // GL_TEXTURE_MAX_ANISOTROPY_EXT
        {
            flushErrors();
    GLfloat texture_max_anisotropy_ext_arr[2] = {0, (GLfloat)0xdeadc0de};
    glGetSamplerParameterfv(sampler_binding, GL_TEXTURE_MAX_ANISOTROPY_EXT, texture_max_anisotropy_ext_arr);
    GLfloat texture_max_anisotropy_ext = texture_max_anisotropy_ext_arr[0];
    assert(texture_max_anisotropy_ext_arr[1] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_TEXTURE_MAX_ANISOTROPY_EXT");
    writer.writeFloat(texture_max_anisotropy_ext);
                writer.endMember();
            }
        }



        // GL_TEXTURE_COMPARE_MODE
        {
            flushErrors();
    GLint texture_compare_mode_arr[2] = {0, (GLint)0xdeadc0de};
    glGetSamplerParameteriv(sampler_binding, GL_TEXTURE_COMPARE_MODE, texture_compare_mode_arr);
    GLint texture_compare_mode = texture_compare_mode_arr[0];
    assert(texture_compare_mode_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_TEXTURE_COMPARE_MODE");
    dumpEnum(writer, texture_compare_mode);
                writer.endMember();
            }
        }

        // GL_TEXTURE_COMPARE_FUNC
        {
            flushErrors();
    GLint texture_compare_func_arr[2] = {0, (GLint)0xdeadc0de};
    glGetSamplerParameteriv(sampler_binding, GL_TEXTURE_COMPARE_FUNC, texture_compare_func_arr);
    GLint texture_compare_func = texture_compare_func_arr[0];
    assert(texture_compare_func_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_TEXTURE_COMPARE_FUNC");
    dumpEnum(writer, texture_compare_func);
                writer.endMember();
            }
        }


        // GL_TEXTURE_SRGB_DECODE_EXT
        {
            flushErrors();
    GLint texture_srgb_decode_ext_arr[2] = {0, (GLint)0xdeadc0de};
    glGetSamplerParameteriv(sampler_binding, GL_TEXTURE_SRGB_DECODE_EXT, texture_srgb_decode_ext_arr);
    GLint texture_srgb_decode_ext = texture_srgb_decode_ext_arr[0];
    assert(texture_srgb_decode_ext_arr[1] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                writer.beginMember("GL_TEXTURE_SRGB_DECODE_EXT");
    dumpEnum(writer, texture_srgb_decode_ext);
                writer.endMember();
            }
        }

           writer.endObject();
           writer.endMember(); // GL_SAMPLER
       }
    }

            writer.endObject();
            writer.endMember(); // GL_TEXTUREi
        }
        glActiveTexture(active_texture);
    }

    {
        GLint max_color_attachments = 0;
        glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &max_color_attachments);
        GLint framebuffer;
            // GL_DRAW_FRAMEBUFFER
            framebuffer = 0;
            glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &framebuffer);
            if (framebuffer) {
                writer.beginMember("GL_DRAW_FRAMEBUFFER");
                writer.beginObject();
                for (GLint i = 0; i < max_color_attachments; ++i) {
                    GLint color_attachment = GL_COLOR_ATTACHMENT0 + i;
                    dumpFramebufferAttachementParameters(writer, context, GL_DRAW_FRAMEBUFFER, color_attachment);
                }
                dumpFramebufferAttachementParameters(writer, context, GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT);
                dumpFramebufferAttachementParameters(writer, context, GL_DRAW_FRAMEBUFFER, GL_STENCIL_ATTACHMENT);
                writer.endObject();
                writer.endMember(); // GL_DRAW_FRAMEBUFFER
            }

            // GL_READ_FRAMEBUFFER
            framebuffer = 0;
            glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &framebuffer);
            if (framebuffer) {
                writer.beginMember("GL_READ_FRAMEBUFFER");
                writer.beginObject();
                for (GLint i = 0; i < max_color_attachments; ++i) {
                    GLint color_attachment = GL_COLOR_ATTACHMENT0 + i;
                    dumpFramebufferAttachementParameters(writer, context, GL_READ_FRAMEBUFFER, color_attachment);
                }
                dumpFramebufferAttachementParameters(writer, context, GL_READ_FRAMEBUFFER, GL_DEPTH_ATTACHMENT);
                dumpFramebufferAttachementParameters(writer, context, GL_READ_FRAMEBUFFER, GL_STENCIL_ATTACHMENT);
                writer.endObject();
                writer.endMember(); // GL_READ_FRAMEBUFFER
            }

    }

    writer.endObject();
    writer.endMember(); // parameters
}

} /*namespace glstate */
