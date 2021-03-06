/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef _UQM_VIDEO_H
#define _UQM_VIDEO_H

#include "options.h"
#include "misc.h"
#include "vidlib.h"
#include "libs/graphics/tfb_draw.h"
#include "types.h"
#include "videodec.h"
#include "libs/sound/sound.h"
#include "libs/tasklib.h"


typedef struct tfb_videoclip
{
	TFB_VideoDecoder *decoder; // decoder to read from
	float length; // total length of clip seconds
	uint32 w, h;

	// video player data
	RECT dst_rect;     // destination screen rect
	RECT src_rect;     // source rect
	MUSIC_REF hAudio;
	Task play_task;
	uint32 frame_time; // time when next frame should be rendered
	TFB_Image* frame;  // frame preped and optimized for rendering
	uint32 cur_frame;  // index of frame currently displayed
	uint32 max_frame_wait;
	bool playing;

	Mutex guard;
	uint32 want_frame; // audio-signaled desired frame index

	void* data; // user-defined data

} TFB_VideoClip;

extern VIDEO_REF _init_video_file(const char *pStr);

#endif // _UQM_VIDEO_H
