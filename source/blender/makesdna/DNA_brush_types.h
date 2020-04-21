/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * The Original Code is Copyright (C) 2005 Blender Foundation.
 * All rights reserved.
 */

/** \file
 * \ingroup DNA
 */

#ifndef __DNA_BRUSH_TYPES_H__
#define __DNA_BRUSH_TYPES_H__

#include "DNA_ID.h"
#include "DNA_curve_types.h"
#include "DNA_texture_types.h" /* for MTex */

//#ifndef MAX_MTEX // XXX Not used?
//#define MAX_MTEX  18
//#endif

struct CurveMapping;
struct Image;
struct MTex;
struct Material;

typedef struct BrushClone {
  /** Image for clone tool. */
  struct Image *image;
  /** Offset of clone image from canvas. */
  float offset[2];
  /** Transparency for drawing of clone image. */
  float alpha;
  char _pad[4];
} BrushClone;

typedef struct BrushGpencilSettings {
  /** Amount of smoothing to apply to newly created strokes. */
  float draw_smoothfac;
  char _pad2[4];
  /** Amount of alpha strength to apply to newly created strokes. */
  float draw_strength;
  /** Amount of jitter to apply to newly created strokes. */
  float draw_jitter;
  /** Angle when the brush has full thickness. */
  float draw_angle;
  /** Factor to apply when angle change (only 90 degrees). */
  float draw_angle_factor;
  /** Factor of randomness for pressure. */
  float draw_random_press;
  /** Factor of strength for strength. */
  float draw_random_strength;
  /** Number of times to apply smooth factor to new strokes. */
  short draw_smoothlvl;
  /** Number of times to subdivide new strokes. */
  short draw_subdivide;
  char _pad[4];

  /** Factor for transparency. */
  float fill_threshold;
  /** Number of pixel to consider the leak is too small (x 2). */
  short fill_leak;
  /** Fill zoom factor */
  short fill_factor;
  int flag2;

  /** Number of simplify steps. */
  int fill_simplylvl;
  /** Type of control lines drawing mode. */
  int fill_draw_mode;
  /** Icon identifier. */
  int icon_id;

  /** Maximum distance before generate new point for very fast mouse movements. */
  int input_samples;
  /** Random factor for UV rotation. */
  float uv_random;
  /** Moved to 'Brush.gpencil_tool'. */
  int brush_type DNA_DEPRECATED;
  /** Soft, hard or stroke. */
  int eraser_mode;
  /** Smooth while drawing factor. */
  float active_smooth;
  /** Factor to apply to strength for soft eraser. */
  float era_strength_f;
  /** Factor to apply to thickness for soft eraser. */
  float era_thickness_f;
  /** Internal grease pencil drawing flags. */
  int flag;

  /** gradient control along y for color */
  float hardeness;
  /** factor xy of shape for dots gradients */
  float aspect_ratio[2];
  /** Simplify adaptive factor */
  float simplify_f;

  /** Mix colorfactor */
  float vertex_factor;
  int vertex_mode;

  /** eGP_Sculpt_Flag. */
  int sculpt_flag;
  /** eGP_Sculpt_Mode_Flag. */
  int sculpt_mode_flag;
  /** Preset type (used to reset brushes - internal). */
  short preset_type;
  char _pad3[2];

  /** Randomness for Hue. */
  float random_hue;
  /** Randomness for Saturation. */
  float random_saturation;
  /** Randomness for Value. */
  float random_value;

  struct CurveMapping *curve_sensitivity;
  struct CurveMapping *curve_strength;
  struct CurveMapping *curve_jitter;

  /* optional link of material to replace default in context */
  /** Material. */
  struct Material *material;
} BrushGpencilSettings;

/* BrushGpencilSettings->preset_type.
 * Use a range for each group and not continuous values.*/
typedef enum eGPBrush_Presets {
  GP_BRUSH_PRESET_UNKNOWN = 0,

  /* Draw 1-99. */
  GP_BRUSH_PRESET_AIRBRUSH = 1,
  GP_BRUSH_PRESET_INK_PEN = 2,
  GP_BRUSH_PRESET_INK_PEN_ROUGH = 3,
  GP_BRUSH_PRESET_MARKER_BOLD = 4,
  GP_BRUSH_PRESET_MARKER_CHISEL = 5,
  GP_BRUSH_PRESET_PEN = 6,
  GP_BRUSH_PRESET_PENCIL_SOFT = 7,
  GP_BRUSH_PRESET_PENCIL = 8,
  GP_BRUSH_PRESET_FILL_AREA = 9,
  GP_BRUSH_PRESET_ERASER_SOFT = 10,
  GP_BRUSH_PRESET_ERASER_HARD = 11,
  GP_BRUSH_PRESET_ERASER_POINT = 12,
  GP_BRUSH_PRESET_ERASER_STROKE = 13,
  GP_BRUSH_PRESET_TINT = 14,

  /* Vertex Paint 100-199. */
  GP_BRUSH_PRESET_VERTEX_DRAW = 100,
  GP_BRUSH_PRESET_VERTEX_BLUR = 101,
  GP_BRUSH_PRESET_VERTEX_AVERAGE = 102,
  GP_BRUSH_PRESET_VERTEX_SMEAR = 103,
  GP_BRUSH_PRESET_VERTEX_REPLACE = 104,

  /* Sculpt 200-299. */
  GP_BRUSH_PRESET_SMOOTH_STROKE = 200,
  GP_BRUSH_PRESET_STRENGTH_STROKE = 201,
  GP_BRUSH_PRESET_THICKNESS_STROKE = 202,
  GP_BRUSH_PRESET_GRAB_STROKE = 203,
  GP_BRUSH_PRESET_PUSH_STROKE = 204,
  GP_BRUSH_PRESET_TWIST_STROKE = 205,
  GP_BRUSH_PRESET_PINCH_STROKE = 206,
  GP_BRUSH_PRESET_RANDOMIZE_STROKE = 207,
  GP_BRUSH_PRESET_CLONE_STROKE = 208,

  /* Weight Paint 300-399. */
  GP_BRUSH_PRESET_DRAW_WEIGHT = 300,
} eGPBrush_Presets;

/* BrushGpencilSettings->gp_flag */
typedef enum eGPDbrush_Flag {
  /* brush use pressure */
  GP_BRUSH_USE_PRESSURE = (1 << 0),
  /* brush use pressure for alpha factor */
  GP_BRUSH_USE_STENGTH_PRESSURE = (1 << 1),
  /* brush use pressure for alpha factor */
  GP_BRUSH_USE_JITTER_PRESSURE = (1 << 2),
  /* fill hide transparent */
  GP_BRUSH_FILL_HIDE = (1 << 6),
  /* show fill help lines */
  GP_BRUSH_FILL_SHOW_HELPLINES = (1 << 7),
  /* lazy mouse */
  GP_BRUSH_STABILIZE_MOUSE = (1 << 8),
  /* lazy mouse override (internal only) */
  GP_BRUSH_STABILIZE_MOUSE_TEMP = (1 << 9),
  /* default eraser brush for quick switch */
  GP_BRUSH_DEFAULT_ERASER = (1 << 10),
  /* settings group */
  GP_BRUSH_GROUP_SETTINGS = (1 << 11),
  /* Random settings group */
  GP_BRUSH_GROUP_RANDOM = (1 << 12),
  /* Keep material assigned to brush */
  GP_BRUSH_MATERIAL_PINNED = (1 << 13),
  /* Do not show fill color while drawing (no lasso mode) */
  GP_BRUSH_DISSABLE_LASSO = (1 << 14),
  /* Do not erase strokes oLcluded */
  GP_BRUSH_OCCLUDE_ERASER = (1 << 15),
  /* Post process trim stroke */
  GP_BRUSH_TRIM_STROKE = (1 << 16),
} eGPDbrush_Flag;

typedef enum eGPDbrush_Flag2 {
  /* Brush use random Hue at stroke level */
  GP_BRUSH_USE_HUE_AT_STROKE = (1 << 0),
  /* Brush use random Saturation at stroke level */
  GP_BRUSH_USE_SAT_AT_STROKE = (1 << 1),
  /* Brush use random Value at stroke level */
  GP_BRUSH_USE_VAL_AT_STROKE = (1 << 2),
  /* Brush use random Pressure at stroke level */
  GP_BRUSH_USE_PRESS_AT_STROKE = (1 << 3),
  /* Brush use random Strength at stroke level */
  GP_BRUSH_USE_STRENGTH_AT_STROKE = (1 << 4),
  /* Brush use random UV at stroke level */
  GP_BRUSH_USE_UV_AT_STROKE = (1 << 5),
} eGPDbrush_Flag2;

/* BrushGpencilSettings->gp_fill_draw_mode */
typedef enum eGP_FillDrawModes {
  GP_FILL_DMODE_BOTH = 0,
  GP_FILL_DMODE_STROKE = 1,
  GP_FILL_DMODE_CONTROL = 2,
} eGP_FillDrawModes;

/* BrushGpencilSettings->gp_eraser_mode */
typedef enum eGP_BrushEraserMode {
  GP_BRUSH_ERASER_SOFT = 0,
  GP_BRUSH_ERASER_HARD = 1,
  GP_BRUSH_ERASER_STROKE = 2,
} eGP_BrushEraserMode;

/* BrushGpencilSettings default brush icons */
typedef enum eGP_BrushIcons {
  GP_BRUSH_ICON_PENCIL = 1,
  GP_BRUSH_ICON_PEN = 2,
  GP_BRUSH_ICON_INK = 3,
  GP_BRUSH_ICON_INKNOISE = 4,
  GP_BRUSH_ICON_BLOCK = 5,
  GP_BRUSH_ICON_MARKER = 6,
  GP_BRUSH_ICON_FILL = 7,
  GP_BRUSH_ICON_ERASE_SOFT = 8,
  GP_BRUSH_ICON_ERASE_HARD = 9,
  GP_BRUSH_ICON_ERASE_STROKE = 10,
  GP_BRUSH_ICON_AIRBRUSH = 11,
  GP_BRUSH_ICON_CHISEL = 12,
  GP_BRUSH_ICON_TINT = 13,
  GP_BRUSH_ICON_VERTEX_DRAW = 14,
  GP_BRUSH_ICON_VERTEX_BLUR = 15,
  GP_BRUSH_ICON_VERTEX_AVERAGE = 16,
  GP_BRUSH_ICON_VERTEX_SMEAR = 17,
  GP_BRUSH_ICON_VERTEX_REPLACE = 18,
  GP_BRUSH_ICON_GPBRUSH_SMOOTH = 19,
  GP_BRUSH_ICON_GPBRUSH_THICKNESS = 20,
  GP_BRUSH_ICON_GPBRUSH_STRENGTH = 21,
  GP_BRUSH_ICON_GPBRUSH_RANDOMIZE = 22,
  GP_BRUSH_ICON_GPBRUSH_GRAB = 23,
  GP_BRUSH_ICON_GPBRUSH_PUSH = 24,
  GP_BRUSH_ICON_GPBRUSH_TWIST = 25,
  GP_BRUSH_ICON_GPBRUSH_PINCH = 26,
  GP_BRUSH_ICON_GPBRUSH_CLONE = 27,
  GP_BRUSH_ICON_GPBRUSH_WEIGHT = 28,
} eGP_BrushIcons;

typedef enum eBrushCurvePreset {
  BRUSH_CURVE_CUSTOM = 0,
  BRUSH_CURVE_SMOOTH = 1,
  BRUSH_CURVE_SPHERE = 2,
  BRUSH_CURVE_ROOT = 3,
  BRUSH_CURVE_SHARP = 4,
  BRUSH_CURVE_LIN = 5,
  BRUSH_CURVE_POW4 = 6,
  BRUSH_CURVE_INVSQUARE = 7,
  BRUSH_CURVE_CONSTANT = 8,
  BRUSH_CURVE_SMOOTHER = 9,
} eBrushCurvePreset;

typedef enum eBrushElasticDeformType {
  BRUSH_ELASTIC_DEFORM_GRAB = 0,
  BRUSH_ELASTIC_DEFORM_GRAB_BISCALE = 1,
  BRUSH_ELASTIC_DEFORM_GRAB_TRISCALE = 2,
  BRUSH_ELASTIC_DEFORM_SCALE = 3,
  BRUSH_ELASTIC_DEFORM_TWIST = 4,
} eBrushElasticDeformType;

typedef enum eBrushClothDeformType {
  BRUSH_CLOTH_DEFORM_DRAG = 0,
  BRUSH_CLOTH_DEFORM_PUSH = 1,
  BRUSH_CLOTH_DEFORM_GRAB = 2,
  BRUSH_CLOTH_DEFORM_PINCH_POINT = 3,
  BRUSH_CLOTH_DEFORM_PINCH_PERPENDICULAR = 4,
  BRUSH_CLOTH_DEFORM_INFLATE = 5,
  BRUSH_CLOTH_DEFORM_EXPAND = 6,
} eBrushClothDeformType;

typedef enum eBrushSmoothDeformType {
  BRUSH_SMOOTH_DEFORM_LAPLACIAN = 0,
  BRUSH_SMOOTH_DEFORM_SURFACE = 1,
} eBrushSmoothDeformType;

typedef enum eBrushClothForceFalloffType {
  BRUSH_CLOTH_FORCE_FALLOFF_RADIAL = 0,
  BRUSH_CLOTH_FORCE_FALLOFF_PLANE = 1,
} eBrushClothForceFalloffType;

typedef enum eBrushPoseOriginType {
  BRUSH_POSE_ORIGIN_TOPOLOGY = 0,
  BRUSH_POSE_ORIGIN_FACE_SETS = 1,
} eBrushPoseOriginType;

/* Gpencilsettings.Vertex_mode */
typedef enum eGp_Vertex_Mode {
  /* Affect to Stroke only. */
  GPPAINT_MODE_STROKE = 0,
  /* Affect to Fill only. */
  GPPAINT_MODE_FILL = 1,
  /* Affect to both. */
  GPPAINT_MODE_BOTH = 2,
} eGp_Vertex_Mode;

/* sculpt_flag */
typedef enum eGP_Sculpt_Flag {
  /* invert the effect of the brush */
  GP_SCULPT_FLAG_INVERT = (1 << 0),
  /* smooth brush affects pressure values as well */
  GP_SCULPT_FLAG_SMOOTH_PRESSURE = (1 << 2),
  /* temporary invert action */
  GP_SCULPT_FLAG_TMP_INVERT = (1 << 3),
} eGP_Sculpt_Flag;

/* sculpt_mode_flag */
typedef enum eGP_Sculpt_Mode_Flag {
  /* apply brush to position */
  GP_SCULPT_FLAGMODE_APPLY_POSITION = (1 << 0),
  /* apply brush to strength */
  GP_SCULPT_FLAGMODE_APPLY_STRENGTH = (1 << 1),
  /* apply brush to thickness */
  GP_SCULPT_FLAGMODE_APPLY_THICKNESS = (1 << 2),
  /* apply brush to uv data */
  GP_SCULPT_FLAGMODE_APPLY_UV = (1 << 3),
} eGP_Sculpt_Mode_Flag;

typedef enum eAutomasking_flag {
  BRUSH_AUTOMASKING_TOPOLOGY = (1 << 0),
  BRUSH_AUTOMASKING_FACE_SETS = (1 << 1),
  BRUSH_AUTOMASKING_BOUNDARY_EDGES = (1 << 2),
  BRUSH_AUTOMASKING_BOUNDARY_FACE_SETS = (1 << 3),
} eAutomasking_flag;

typedef struct Brush {
  ID id;

  struct BrushClone clone;
  /** Falloff curve. */
  struct CurveMapping *curve;
  struct MTex mtex;
  struct MTex mask_mtex;

  struct Brush *toggle_brush;

  struct ImBuf *icon_imbuf;
  PreviewImage *preview;
  /** Color gradient. */
  struct ColorBand *gradient;
  struct PaintCurve *paint_curve;

  /** 1024 = FILE_MAX. */
  char icon_filepath[1024];

  float normal_weight;
  /** Rake actual data (not texture), used for sculpt. */
  float rake_factor;

  /** Blend mode. */
  short blend;
  /** #eObjectMode: to see if the brush is compatible, use for display only. */
  short ob_mode;
  /** Brush weight. */
  float weight;
  /** Brush diameter. */
  int size;
  /** General purpose flags. */
  int flag;
  int flag2;
  int sampling_flag;

  /** Pressure influence for mask. */
  int mask_pressure;
  /** Jitter the position of the brush. */
  float jitter;
  /** Absolute jitter in pixels. */
  int jitter_absolute;
  int overlay_flags;
  /** Spacing of paint operations. */
  int spacing;
  /** Turning radius (in pixels) for smooth stroke. */
  int smooth_stroke_radius;
  /** Higher values limit fast changes in the stroke direction. */
  float smooth_stroke_factor;
  /** Paint operations / second (airbrush). */
  float rate;

  /** Color. */
  float rgb[3];
  /** Opacity. */
  float alpha;

  /** Background color. */
  float secondary_rgb[3];

  /** Rate */
  float dash_ratio;
  int dash_samples;

  /** The direction of movement for sculpt vertices. */
  int sculpt_plane;

  /** Offset for plane brushes (clay, flatten, fill, scrape). */
  float plane_offset;

  int gradient_spacing;
  /** Source for stroke color gradient application. */
  char gradient_stroke_mode;
  /** Source for fill tool color gradient application. */
  char gradient_fill_mode;

  char _pad0[1];

  /** Projection shape (sphere, circle). */
  char falloff_shape;
  float falloff_angle;

  /** Active sculpt tool. */
  char sculpt_tool;
  /** Active sculpt tool. */
  char uv_sculpt_tool;
  /** Active vertex paint. */
  char vertexpaint_tool;
  /** Active weight paint. */
  char weightpaint_tool;
  /** Active image paint tool. */
  char imagepaint_tool;
  /** Enum eBrushMaskTool, only used if sculpt_tool is SCULPT_TOOL_MASK. */
  char mask_tool;
  /** Active grease pencil tool. */
  char gpencil_tool;
  /** Active grease pencil vertex tool. */
  char gpencil_vertex_tool;
  /** Active grease pencil sculpt tool. */
  char gpencil_sculpt_tool;
  /** Active grease pencil weight tool. */
  char gpencil_weight_tool;
  char _pad1[6];

  float autosmooth_factor;

  float topology_rake_factor;

  float crease_pinch_factor;

  float normal_radius_factor;
  float area_radius_factor;

  float plane_trim;
  /** Affectable height of brush (layer height for layer tool, i.e.). */
  float height;

  float texture_sample_bias;

  int curve_preset;
  float hardness;

  /* automasking */
  int automasking_flags;
  int automasking_boundary_edges_propagation_steps;

  /* Factor that controls the shape of the brush tip by rounding the corners of a square. */
  /* 0.0 value produces a square, 1.0 produces a circle. */
  float tip_roundness;

  int elastic_deform_type;
  float elastic_deform_volume_preservation;

  /* pose */
  float pose_offset;
  int pose_smooth_iterations;
  int pose_ik_segments;
  int pose_origin_type;

  /* cloth */
  int cloth_deform_type;
  int cloth_force_falloff_type;

  float cloth_mass;
  float cloth_damping;

  float cloth_sim_limit;
  float cloth_sim_falloff;

  /* smooth */
  int smooth_deform_type;
  float surface_smooth_shape_preservation;
  float surface_smooth_current_vertex;
  int surface_smooth_iterations;

  /* multiplane scrape */
  float multiplane_scrape_angle;

  /* overlay */
  int texture_overlay_alpha;
  int mask_overlay_alpha;
  int cursor_overlay_alpha;

  float unprojected_radius;

  /* soften/sharpen */
  float sharp_threshold;
  int blur_kernel_radius;
  int blur_mode;

  /* fill tool */
  float fill_threshold;

  float add_col[4];
  float sub_col[4];

  float stencil_pos[2];
  float stencil_dimension[2];

  float mask_stencil_pos[2];
  float mask_stencil_dimension[2];

  struct BrushGpencilSettings *gpencil_settings;

} Brush;

/* Struct to hold palette colors for sorting. */
typedef struct tPaletteColorHSV {
  float rgb[3];
  float value;
  float h;
  float s;
  float v;
} tPaletteColorHSV;

typedef struct PaletteColor {
  struct PaletteColor *next, *prev;
  /* two values, one to store rgb, other to store values for sculpt/weight */
  float rgb[3];
  float value;
} PaletteColor;

typedef struct Palette {
  ID id;

  /** Pointer to individual colors. */
  ListBase colors;

  int active_color;
  char _pad[4];
} Palette;

typedef struct PaintCurvePoint {
  /** Bezier handle. */
  BezTriple bez;
  /** Pressure on that point. */
  float pressure;
} PaintCurvePoint;

typedef struct PaintCurve {
  ID id;
  /** Points of curve. */
  PaintCurvePoint *points;
  int tot_points;
  /** Index where next point will be added. */
  int add_index;
} PaintCurve;

/* Brush.gradient_source */
typedef enum eBrushGradientSourceStroke {
  BRUSH_GRADIENT_PRESSURE = 0,       /* gradient from pressure */
  BRUSH_GRADIENT_SPACING_REPEAT = 1, /* gradient from spacing */
  BRUSH_GRADIENT_SPACING_CLAMP = 2,  /* gradient from spacing */
} eBrushGradientSourceStroke;

typedef enum eBrushGradientSourceFill {
  BRUSH_GRADIENT_LINEAR = 0, /* gradient from pressure */
  BRUSH_GRADIENT_RADIAL = 1, /* gradient from spacing */
} eBrushGradientSourceFill;

/* Brush.flag */
typedef enum eBrushFlags {
  BRUSH_AIRBRUSH = (1 << 0),
  BRUSH_INVERT_TO_SCRAPE_FILL = (1 << 1),
  BRUSH_ALPHA_PRESSURE = (1 << 2),
  BRUSH_SIZE_PRESSURE = (1 << 3),
  BRUSH_JITTER_PRESSURE = (1 << 4),
  BRUSH_SPACING_PRESSURE = (1 << 5),
  BRUSH_ORIGINAL_PLANE = (1 << 6),
  BRUSH_GRAB_ACTIVE_VERTEX = (1 << 7),
  BRUSH_ANCHORED = (1 << 8),
  BRUSH_DIR_IN = (1 << 9),
  BRUSH_SPACE = (1 << 10),
  BRUSH_SMOOTH_STROKE = (1 << 11),
  BRUSH_PERSISTENT = (1 << 12),
  BRUSH_ACCUMULATE = (1 << 13),
  BRUSH_LOCK_ALPHA = (1 << 14),
  BRUSH_ORIGINAL_NORMAL = (1 << 15),
  BRUSH_OFFSET_PRESSURE = (1 << 16),
  BRUSH_SCENE_SPACING = (1 << 17),
  BRUSH_SPACE_ATTEN = (1 << 18),
  BRUSH_ADAPTIVE_SPACE = (1 << 19),
  BRUSH_LOCK_SIZE = (1 << 20),
  BRUSH_USE_GRADIENT = (1 << 21),
  BRUSH_EDGE_TO_EDGE = (1 << 22),
  BRUSH_DRAG_DOT = (1 << 23),
  BRUSH_INVERSE_SMOOTH_PRESSURE = (1 << 24),
  BRUSH_FRONTFACE_FALLOFF = (1 << 25),
  BRUSH_PLANE_TRIM = (1 << 26),
  BRUSH_FRONTFACE = (1 << 27),
  BRUSH_CUSTOM_ICON = (1 << 28),
  BRUSH_LINE = (1 << 29),
  BRUSH_ABSOLUTE_JITTER = (1 << 30),
  BRUSH_CURVE = (1u << 31),
} eBrushFlags;

/* Brush.sampling_flag */
typedef enum eBrushSamplingFlags {
  BRUSH_PAINT_ANTIALIASING = (1 << 0),
} eBrushSamplingFlags;

/* Brush.flag2 */
typedef enum eBrushFlags2 {
  BRUSH_MULTIPLANE_SCRAPE_DYNAMIC = (1 << 0),
  BRUSH_MULTIPLANE_SCRAPE_PLANES_PREVIEW = (1 << 1),
  BRUSH_POSE_IK_ANCHORED = (1 << 2),
} eBrushFlags2;

typedef enum {
  BRUSH_MASK_PRESSURE_RAMP = (1 << 1),
  BRUSH_MASK_PRESSURE_CUTOFF = (1 << 2),
} BrushMaskPressureFlags;

/* Brush.overlay_flags */
typedef enum eOverlayFlags {
  BRUSH_OVERLAY_CURSOR = (1),
  BRUSH_OVERLAY_PRIMARY = (1 << 1),
  BRUSH_OVERLAY_SECONDARY = (1 << 2),
  BRUSH_OVERLAY_CURSOR_OVERRIDE_ON_STROKE = (1 << 3),
  BRUSH_OVERLAY_PRIMARY_OVERRIDE_ON_STROKE = (1 << 4),
  BRUSH_OVERLAY_SECONDARY_OVERRIDE_ON_STROKE = (1 << 5),
} eOverlayFlags;

#define BRUSH_OVERLAY_OVERRIDE_MASK \
  (BRUSH_OVERLAY_CURSOR_OVERRIDE_ON_STROKE | BRUSH_OVERLAY_PRIMARY_OVERRIDE_ON_STROKE | \
   BRUSH_OVERLAY_SECONDARY_OVERRIDE_ON_STROKE)

/* Brush.sculpt_tool */
typedef enum eBrushSculptTool {
  SCULPT_TOOL_DRAW = 1,
  SCULPT_TOOL_SMOOTH = 2,
  SCULPT_TOOL_PINCH = 3,
  SCULPT_TOOL_INFLATE = 4,
  SCULPT_TOOL_GRAB = 5,
  SCULPT_TOOL_LAYER = 6,
  SCULPT_TOOL_FLATTEN = 7,
  SCULPT_TOOL_CLAY = 8,
  SCULPT_TOOL_FILL = 9,
  SCULPT_TOOL_SCRAPE = 10,
  SCULPT_TOOL_NUDGE = 11,
  SCULPT_TOOL_THUMB = 12,
  SCULPT_TOOL_SNAKE_HOOK = 13,
  SCULPT_TOOL_ROTATE = 14,
  SCULPT_TOOL_SIMPLIFY = 15,
  SCULPT_TOOL_CREASE = 16,
  SCULPT_TOOL_BLOB = 17,
  SCULPT_TOOL_CLAY_STRIPS = 18,
  SCULPT_TOOL_MASK = 19,
  SCULPT_TOOL_DRAW_SHARP = 20,
  SCULPT_TOOL_ELASTIC_DEFORM = 21,
  SCULPT_TOOL_POSE = 22,
  SCULPT_TOOL_MULTIPLANE_SCRAPE = 23,
  SCULPT_TOOL_SLIDE_RELAX = 24,
  SCULPT_TOOL_CLAY_THUMB = 25,
  SCULPT_TOOL_CLOTH = 26,
  SCULPT_TOOL_DRAW_FACE_SETS = 27,
} eBrushSculptTool;

/* Brush.uv_sculpt_tool */
typedef enum eBrushUVSculptTool {
  UV_SCULPT_TOOL_GRAB = 0,
  UV_SCULPT_TOOL_RELAX = 1,
  UV_SCULPT_TOOL_PINCH = 2,
} eBrushUVSculptTool;

/** When #BRUSH_ACCUMULATE is used */
#define SCULPT_TOOL_HAS_ACCUMULATE(t) \
  ELEM(t, \
       SCULPT_TOOL_DRAW, \
       SCULPT_TOOL_DRAW_SHARP, \
       SCULPT_TOOL_SLIDE_RELAX, \
       SCULPT_TOOL_CREASE, \
       SCULPT_TOOL_BLOB, \
       SCULPT_TOOL_INFLATE, \
       SCULPT_TOOL_CLAY, \
       SCULPT_TOOL_CLAY_STRIPS, \
       SCULPT_TOOL_CLAY_THUMB, \
       SCULPT_TOOL_ROTATE, \
       SCULPT_TOOL_SCRAPE, \
       SCULPT_TOOL_FLATTEN)

#define SCULPT_TOOL_HAS_NORMAL_WEIGHT(t) \
  ELEM(t, SCULPT_TOOL_GRAB, SCULPT_TOOL_SNAKE_HOOK, SCULPT_TOOL_ELASTIC_DEFORM)

#define SCULPT_TOOL_HAS_RAKE(t) ELEM(t, SCULPT_TOOL_SNAKE_HOOK)

#define SCULPT_TOOL_HAS_DYNTOPO(t) \
  (ELEM(t, /* These brushes, as currently coded, cannot support dynamic topology */ \
        SCULPT_TOOL_GRAB, \
        SCULPT_TOOL_ROTATE, \
        SCULPT_TOOL_CLOTH, \
        SCULPT_TOOL_THUMB, \
        SCULPT_TOOL_LAYER, \
        SCULPT_TOOL_DRAW_SHARP, \
        SCULPT_TOOL_SLIDE_RELAX, \
        SCULPT_TOOL_ELASTIC_DEFORM, \
        SCULPT_TOOL_POSE, \
        SCULPT_TOOL_DRAW_FACE_SETS, \
\
        /* These brushes could handle dynamic topology, \ \
         * but user feedback indicates it's better not to */ \
        SCULPT_TOOL_SMOOTH, \
        SCULPT_TOOL_MASK) == 0)

#define SCULPT_TOOL_HAS_TOPOLOGY_RAKE(t) \
  (ELEM(t, /* These brushes, as currently coded, cannot support topology rake. */ \
        SCULPT_TOOL_GRAB, \
        SCULPT_TOOL_ROTATE, \
        SCULPT_TOOL_THUMB, \
        SCULPT_TOOL_DRAW_SHARP, \
        SCULPT_TOOL_SLIDE_RELAX, \
        SCULPT_TOOL_MASK) == 0)

/* ImagePaintSettings.tool */
typedef enum eBrushImagePaintTool {
  PAINT_TOOL_DRAW = 0,
  PAINT_TOOL_SOFTEN = 1,
  PAINT_TOOL_SMEAR = 2,
  PAINT_TOOL_CLONE = 3,
  PAINT_TOOL_FILL = 4,
  PAINT_TOOL_MASK = 5,
} eBrushImagePaintTool;

typedef enum eBrushVertexPaintTool {
  VPAINT_TOOL_DRAW = 0,
  VPAINT_TOOL_BLUR = 1,
  VPAINT_TOOL_AVERAGE = 2,
  VPAINT_TOOL_SMEAR = 3,
} eBrushVertexPaintTool;

typedef enum eBrushWeightPaintTool {
  WPAINT_TOOL_DRAW = 0,
  WPAINT_TOOL_BLUR = 1,
  WPAINT_TOOL_AVERAGE = 2,
  WPAINT_TOOL_SMEAR = 3,
} eBrushWeightPaintTool;

/* BrushGpencilSettings->brush type */
typedef enum eBrushGPaintTool {
  GPAINT_TOOL_DRAW = 0,
  GPAINT_TOOL_FILL = 1,
  GPAINT_TOOL_ERASE = 2,
  GPAINT_TOOL_TINT = 3,
} eBrushGPaintTool;

/* BrushGpencilSettings->brush type */
typedef enum eBrushGPVertexTool {
  GPVERTEX_TOOL_DRAW = 0,
  GPVERTEX_TOOL_BLUR = 1,
  GPVERTEX_TOOL_AVERAGE = 2,
  GPVERTEX_TOOL_TINT = 3,
  GPVERTEX_TOOL_SMEAR = 4,
  GPVERTEX_TOOL_REPLACE = 5,
} eBrushGPVertexTool;

/* BrushGpencilSettings->brush type */
typedef enum eBrushGPSculptTool {
  GPSCULPT_TOOL_SMOOTH = 0,
  GPSCULPT_TOOL_THICKNESS = 1,
  GPSCULPT_TOOL_STRENGTH = 2,
  GPSCULPT_TOOL_GRAB = 3,
  GPSCULPT_TOOL_PUSH = 4,
  GPSCULPT_TOOL_TWIST = 5,
  GPSCULPT_TOOL_PINCH = 6,
  GPSCULPT_TOOL_RANDOMIZE = 7,
  GPSCULPT_TOOL_CLONE = 8,
} eBrushGPSculptTool;

/* BrushGpencilSettings->brush type */
typedef enum eBrushGPWeightTool {
  GPWEIGHT_TOOL_DRAW = 0,
} eBrushGPWeightTool;

/* direction that the brush displaces along */
enum {
  SCULPT_DISP_DIR_AREA = 0,
  SCULPT_DISP_DIR_VIEW = 1,
  SCULPT_DISP_DIR_X = 2,
  SCULPT_DISP_DIR_Y = 3,
  SCULPT_DISP_DIR_Z = 4,
};

typedef enum {
  BRUSH_MASK_DRAW = 0,
  BRUSH_MASK_SMOOTH = 1,
} BrushMaskTool;

/* blur kernel types, Brush.blur_mode */
typedef enum eBlurKernelType {
  KERNEL_GAUSSIAN,
  KERNEL_BOX,
} eBlurKernelType;

/* Brush.falloff_shape */
enum {
  PAINT_FALLOFF_SHAPE_SPHERE = 0,
  PAINT_FALLOFF_SHAPE_TUBE = 1,
};

#define MAX_BRUSH_PIXEL_RADIUS 500
#define GP_MAX_BRUSH_PIXEL_RADIUS 1000

#endif /* __DNA_BRUSH_TYPES_H__ */
