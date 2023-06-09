/* 
 * This file is part of the Nautilus AeroKernel developed
 * by the Hobbes and V3VEE Projects with funding from the 
 * United States National  Science Foundation and the Department of Energy.  
 *
 * The V3VEE Project is a joint project between Northwestern University
 * and the University of New Mexico.  The Hobbes Project is a collaboration
 * led by Sandia National Laboratories that includes several national 
 * laboratories and universities. You can find out more at:
 * http://www.v3vee.org  and
 * http://xstack.sandia.gov/hobbes
 *
 * Copyright (c) 2020, Peter Dinda <pdinda@northwestern.edu>
 * Copyright (c) 2020, The Interweaving Project  <http://interweaving.org>
 * All rights reserved.
 *
 * Author: Peter Dinda <pdinda@northwestern.edu>
 *
 * Author: Peter Dinda <pdinda@northwestern.edu>
 *
 * This is free software.  You are permitted to use,
 * redistribute, and modify it as specified in the file "LICENSE.txt".
 */

#include <nautilus/nautilus.h>
#include <nautilus/dev.h>
#include <nautilus/gpudev.h>
#include <nautilus/timer.h>
#include <nautilus/shell.h>
#include <nautilus/libccompat.h>

#ifndef NAUT_CONFIG_DEBUG_GPUDEV
#undef DEBUG_PRINT
#define DEBUG_PRINT(fmt, args...) 
#endif

#define ERROR(fmt, args...) ERROR_PRINT("gpudev: " fmt, ##args)
#define DEBUG(fmt, args...) DEBUG_PRINT("gpudev: " fmt, ##args)
#define INFO(fmt, args...) INFO_PRINT("gpudev: " fmt, ##args)




#if 0
static spinlock_t state_lock;

#define STATE_LOCK_CONF uint8_t _state_lock_flags
#define STATE_LOCK() _state_lock_flags = spin_lock_irq_save(&state_lock)
#define STATE_UNLOCK() spin_unlock_irq_restore(&state_lock, _state_lock_flags);

#endif

int nk_gpu_dev_init()
{
    INFO("init\n");
    return 0;
}

int nk_gpu_dev_deinit()
{
    INFO("deinit\n");
    return 0;
}


struct nk_gpu_dev * nk_gpu_dev_register(char *name, uint64_t flags, struct nk_gpu_dev_int *inter, void *state)
{
    INFO("register device %s\n",name);
    return (struct nk_gpu_dev *) nk_dev_register(name,NK_DEV_GRAPHICS,flags,(struct nk_dev_int *)inter,state);
}

int                   nk_gpu_dev_unregister(struct nk_gpu_dev *d)
{
    INFO("unregister device %s\n", d->dev.name);
    return nk_dev_unregister((struct nk_dev *)d);
}

struct nk_gpu_dev * nk_gpu_dev_find(char *name)
{
    DEBUG("find %s\n",name);
    struct nk_dev *d = nk_dev_find(name);
    if (d->type!=NK_DEV_GRAPHICS) {
	DEBUG("%s not found\n",name);
	return 0;
    } else {
	DEBUG("%s found\n",name);
	return (struct nk_gpu_dev*) d;
    }
}


#define BOILERPLATE(str,f,args...)					\
    struct nk_dev *d = (struct nk_dev *)(&(dev->dev));			\
    struct nk_gpu_dev_int *di = (struct nk_gpu_dev_int *)(d->interface); \
									\
    DEBUG(str " of %s\n",d->name);					\
									\
    if (di && di->f) {							\
	return di->f(d->state,##args);					\
    } else {								\
	ERROR(str " not supported on %s\n", d->name);			\
	return -1;							\
    }



int nk_gpu_dev_get_available_modes(nk_gpu_dev_t *dev, nk_gpu_dev_video_mode_t modes[], uint32_t *num)
{
    BOILERPLATE("get available modes",get_available_modes,modes,num);
}
    
int nk_gpu_dev_get_mode(nk_gpu_dev_t *dev, nk_gpu_dev_video_mode_t *mode)
{
    BOILERPLATE("get mode",get_mode,mode);
}

int nk_gpu_dev_set_mode(nk_gpu_dev_t *dev, nk_gpu_dev_video_mode_t *mode)
{
    BOILERPLATE("set mode",set_mode,mode);
}

int nk_gpu_dev_flush(nk_gpu_dev_t *dev)
{
    BOILERPLATE("flush",flush);
}

int nk_gpu_dev_text_set_char(nk_gpu_dev_t *dev, nk_gpu_dev_coordinate_t *location, nk_gpu_dev_char_t *val)
{
    BOILERPLATE("text set char",text_set_char,location,val);
}

int nk_gpu_dev_text_set_cursor(nk_gpu_dev_t *dev, nk_gpu_dev_coordinate_t *location, uint32_t flags)
{
    BOILERPLATE("text set cursor",text_set_cursor,location,flags);
}
    
int nk_gpu_dev_graphics_set_clipping_box(nk_gpu_dev_t *dev, nk_gpu_dev_box_t *box)
{
    BOILERPLATE("graphics set clipping box",graphics_set_clipping_box,box);
}

int nk_gpu_dev_graphics_set_clipping_region(nk_gpu_dev_t *dev, nk_gpu_dev_region_t *region)
{
    BOILERPLATE("graphics set clipping region",graphics_set_clipping_region,region);
}

int nk_gpu_dev_graphics_draw_pixel(nk_gpu_dev_t *dev, nk_gpu_dev_coordinate_t *location, nk_gpu_dev_pixel_t *pixel)
{
    BOILERPLATE("graphics draw pixel",graphics_draw_pixel,location,pixel);
}

int nk_gpu_dev_graphics_draw_line(nk_gpu_dev_t *dev, nk_gpu_dev_coordinate_t *start, nk_gpu_dev_coordinate_t *end, nk_gpu_dev_pixel_t *pixel)
{
    BOILERPLATE("graphics draw line",graphics_draw_line,start,end,pixel);
}

int nk_gpu_dev_graphics_draw_poly(nk_gpu_dev_t *dev, nk_gpu_dev_coordinate_t *coord_list, uint32_t count, nk_gpu_dev_pixel_t *pixel)
{
    BOILERPLATE("graphics draw poly",graphics_draw_poly,coord_list,count,pixel);
}

int nk_gpu_dev_graphics_fill_box_with_pixel(nk_gpu_dev_t *dev, nk_gpu_dev_box_t *box, nk_gpu_dev_pixel_t *pixel, nk_gpu_dev_bit_blit_op_t op)
{
    BOILERPLATE("graphics fill box with pixel",graphics_fill_box_with_pixel,box,pixel,op);
}

int nk_gpu_dev_graphics_fill_box_with_bitmap(nk_gpu_dev_t *dev, nk_gpu_dev_box_t *box, nk_gpu_dev_bitmap_t *bitmap, nk_gpu_dev_bit_blit_op_t op)
{
    BOILERPLATE("graphics fill box with bitmap",graphics_fill_box_with_bitmap,box,bitmap,op);
}

int nk_gpu_dev_graphics_copy_box(nk_gpu_dev_t *dev, nk_gpu_dev_box_t *source_box, nk_gpu_dev_box_t *dest_box, nk_gpu_dev_bit_blit_op_t op)
{
    BOILERPLATE("graphics copy box",graphics_copy_box,source_box,dest_box,op);
}

int nk_gpu_dev_graphics_draw_text(nk_gpu_dev_t *dev, nk_gpu_dev_coordinate_t *location, nk_gpu_dev_font_t *font, char *string)
{
    BOILERPLATE("graphics draw text",graphics_draw_text,location,font,string);
}


int nk_gpu_dev_graphics_set_cursor_bitmap(nk_gpu_dev_t *dev, nk_gpu_dev_bitmap_t *bitmap)
{
    BOILERPLATE("graphics set cursor bitmap",graphics_set_cursor_bitmap,bitmap);
}

int nk_gpu_dev_graphics_set_cursor(nk_gpu_dev_t *dev, nk_gpu_dev_coordinate_t *location)
{
    BOILERPLATE("graphics set cursor",graphics_set_cursor, location);
}


nk_gpu_dev_bitmap_t *nk_gpu_dev_bitmap_create(uint32_t width, uint32_t height)
{
    uint64_t size = sizeof(nk_gpu_dev_bitmap_t)+sizeof(nk_gpu_dev_pixel_t)*width*height;
    nk_gpu_dev_bitmap_t *b = malloc(size);

    if (!b) {
	ERROR("failed to allocate bitmap\n");
	return 0;
    }

    memset(b,0,size);

    b->width=width;
    b->height=height;
    
    return b;
}

void                 nk_gpu_dev_bitmap_destroy(nk_gpu_dev_bitmap_t *bitmap)
{
    free(bitmap);
}

#define CEIL_DIV(x,y) ((x/y) + !!(x%y))

nk_gpu_dev_font_t   *nk_gpu_dev_font_create(uint32_t width, uint32_t height)
{
    uint64_t numbits = 256 * width * height;
    uint64_t size = sizeof(nk_gpu_dev_font_t)+CEIL_DIV(numbits,8);
    nk_gpu_dev_font_t *f = malloc(size);

    if (!f) {
	ERROR("failed to allocate font\n");
	return 0;
    }

    memset(f,0,size);

    f->width=width;
    f->height=height;
    
    return f;
}

void                 nk_gpu_dev_font_destroy(nk_gpu_dev_font_t *font)
{
    free(font);
}
    

#define MAX_MODES 64

#define PRINT_MODE(spec, count, m)					\
    nk_vc_printf(spec "mode %d: %s %u by %u, offsets %u %u %u %u, flags 0x%lx, mouse %u by %u\n", \
		 (count),						\
		 (m)->type==NK_GPU_DEV_MODE_TYPE_TEXT ? "text" :		\
		 (m)->type==NK_GPU_DEV_MODE_TYPE_GRAPHICS_2D ? "graphics (2d)" : "UNKNOWN", \
		 (m)->width, (m)->height,					\
		 (m)->channel_offset[0], (m)->channel_offset[1], (m)->channel_offset[2], (m)->channel_offset[3], \
		 (m)->flags,						\
		 (m)->mouse_cursor_width, (m)->mouse_cursor_height)

// Helper macro for checking the result of a call
#define CHECK(x) if (x) { nk_gpu_dev_set_mode(d,&prevmode); nk_vc_printf("failed to do " #x "\n"); return -1; }


static int handle_gputest (char * buf, void * priv)
{
    char name[32];
    struct nk_gpu_dev *d;
    nk_gpu_dev_video_mode_t modes[MAX_MODES], prevmode, *curmode;
    uint32_t nummodes=MAX_MODES;

    if ((sscanf(buf,"gputest %s",name)!=1)) { 
	nk_vc_printf("gputest devname\n",buf);
	return -1;
    }
    
    if (!(d=nk_gpu_dev_find(name))) { 
        nk_vc_printf("Can't find %s\n",name);
        return -1;
    }

    if (nk_gpu_dev_get_mode(d,&prevmode)) {
	nk_vc_printf("Can't get mode\n");
	return -1;
    }

    PRINT_MODE("current ",0,&prevmode);
    
    if (nk_gpu_dev_get_available_modes(d,modes,&nummodes)) {
        nk_vc_printf("Can't get available modes from %s\n",name);
        return -1;
    }

    uint32_t i, sel=-1;
    
    nk_vc_printf("Available modes are:\n");
    for (i=0;i<nummodes;i++) {
	PRINT_MODE("",i,&modes[i]);
	if (modes[i].type==NK_GPU_DEV_MODE_TYPE_GRAPHICS_2D) {
	    sel = i;
	}
    }
    if (sel==-1) {
	nk_vc_printf("No graphics mode available (huh?) !!!!\n");
	return -1;
    } else {
	nk_vc_printf("Using first graphics mode (%u)\n",sel);
    }

    if (nk_gpu_dev_set_mode(d,&modes[sel])) {
	nk_vc_printf("Failed to set graphics mode....\n");
	return -1;
    }

    curmode = &modes[sel];

    // assume that clipping (if available) is set to whole screen


    // Add your own test code here. You can remove this default test code we wrote
    //
    // WRITE ME!

    //*** start of existing test ***

    // flush the initial display
    CHECK(nk_gpu_dev_flush(d));
    nk_vc_printf("Initial flush of the screen\n");
    nk_sleep(5000000000UL); // five seconds

    // draw some RED pixels on the top part of the screen
    nk_gpu_dev_pixel_t pixel;
    NK_GPU_DEV_PIXEL_SET_RGBA(curmode,&pixel,0xFF,0,0,0); // red
    for (int x=0; x<curmode->width; x++) {
	for (int y=0; y<10; y++) {
	    nk_gpu_dev_coordinate_t location;
	    location.x = x;
	    location.y = y;
	    nk_gpu_dev_graphics_draw_pixel(d, &location, &pixel);
	}
    }
    CHECK(nk_gpu_dev_flush(d));
    nk_vc_printf("Drew some RED pixels\n");
    nk_sleep(5000000000UL); // five seconds

    // draw some horizontal WHITE lines every fourth of the screen from top to bottom
    nk_gpu_dev_pixel_t line_pixel;
    NK_GPU_DEV_PIXEL_SET_RGBA(curmode,&line_pixel,0xFF,0xFF,0xFF,0); // white
    for (int y=0; y<curmode->height; y+=(curmode->height/4)) {
	nk_gpu_dev_coordinate_t start;
	start.x = 0;
	start.y = y;
	nk_gpu_dev_coordinate_t end;
	end.x = curmode->width;
	end.y = y;
	nk_gpu_dev_graphics_draw_line(d, &start, &end, &line_pixel);
    }
    CHECK(nk_gpu_dev_flush(d));
    nk_vc_printf("Drew some WHITE lines\n");
    nk_sleep(5000000000UL); // five seconds

    // draw a green rectangle in the middle of the screen
    nk_gpu_dev_pixel_t poly_pixel;
    NK_GPU_DEV_PIXEL_SET_RGBA(curmode,&poly_pixel,0,0xFF,0,0); //green
    nk_gpu_dev_coordinate_t poly[4];
    poly[0].x = curmode->width/3;
    poly[0].y = curmode->height/3 + 50;
    poly[1].x = curmode->width/3 * 2;
    poly[1].y = curmode->height/3;
    poly[2].x = curmode->width/3 * 2;
    poly[2].y = curmode->height/3 * 2;
    poly[3].x = curmode->width/3;
    poly[3].y = (curmode->height/3 * 2) + 50;
    nk_gpu_dev_graphics_draw_poly(d, poly, 4, &poly_pixel);
    CHECK(nk_gpu_dev_flush(d));
    nk_vc_printf("Drew a GREEN rectangle\n");
    nk_sleep(5000000000UL); // five seconds

    // draw a box over the entire screen
    nk_gpu_dev_box_t box;
    box.x = 0;
    box.y = 0;
    box.width = curmode->width;
    box.height = curmode->height;
    nk_gpu_dev_pixel_t box_pixel;
    NK_GPU_DEV_PIXEL_SET_RGBA(curmode,&box_pixel,0x6a,0x0d,0xad,0);
    CHECK(nk_gpu_dev_graphics_fill_box_with_pixel(d,
                                                  &box,
                                                  &box_pixel,
                                                  NK_GPU_DEV_BIT_BLIT_OP_COPY));
    CHECK(nk_gpu_dev_flush(d));
    nk_vc_printf("Cleared screen to PURPLE\n");
    nk_sleep(5000000000UL); // five seconds

    // draw a bitmap apple image
    extern int image_start;
    nk_gpu_dev_bitmap_t *appleLogo = (nk_gpu_dev_bitmap_t *)&image_start;
    box.x = 20;
    box.y = 20;
    box.width = 300;
    box.height = 300;
    CHECK(nk_gpu_dev_graphics_fill_box_with_bitmap(d,
                                                  &box,
                                                  appleLogo,
                                                  NK_GPU_DEV_BIT_BLIT_OP_COPY));
    CHECK(nk_gpu_dev_flush(d));
    nk_vc_printf("Drew an APPLE_LOGO image\n");
    nk_sleep(5000000000UL); // five seconds

    nk_gpu_dev_box_t source_box;
    source_box.x = 20;
    source_box.y = 20;
    source_box.width = 176; // image width of apple logo picture
    source_box.height = 205; // image height of apple logo picture
    nk_gpu_dev_box_t dest_box;
    dest_box.x = curmode->width - 200;
    dest_box.y = curmode->height - 250;
    dest_box.width = 176; // image width of apple logo picture
    dest_box.height = 205; // image height of apple logo picture
    CHECK(nk_gpu_dev_graphics_copy_box(d,
                                       &source_box,
                                       &dest_box,
                                       NK_GPU_DEV_BIT_BLIT_OP_COPY));
    CHECK(nk_gpu_dev_flush(d));
    nk_vc_printf("COPY BOX of apple logo\n");
    nk_sleep(5000000000UL); // five seconds


    extern int image_clip;
    nk_gpu_dev_bitmap_t *appleLogoClip = (nk_gpu_dev_bitmap_t *)&image_clip;

    nk_gpu_dev_box_t clip_box;
    clip_box.x = curmode->width - 170;
    clip_box.y = 95;
    clip_box.width = 126;
    clip_box.height = 100;

    box.x = curmode->width - 200;
    box.y = 20;
    box.width = 176; // image width of apple logo picture
    box.height = 205; // image height of apple logo picture

    CHECK(nk_gpu_dev_graphics_set_clipping_box(d, &clip_box));
    CHECK(nk_gpu_dev_graphics_fill_box_with_bitmap(d,
                                                   &box,
                                                   appleLogoClip,
                                                   NK_GPU_DEV_BIT_BLIT_OP_COPY));

    CHECK(nk_gpu_dev_flush(d));
    nk_vc_printf("CLIP BOX of apple logo\n");
    nk_sleep(5000000000UL); // five seconds




    //*** end of existing test ***


    nk_vc_printf("Test complete. Reseting to original mode\n");
    if (nk_gpu_dev_set_mode(d,&prevmode)) {
	nk_vc_printf("Cannot switch back to previous mode\n");
	return -1;
    }

    nk_vc_printf("Basic gputest complete\n");

    return 0;
}


static struct shell_cmd_impl gputest_impl = {
    .cmd      = "gputest",
    .help_str = "gputest dev",
    .handler  = handle_gputest,
};
nk_register_shell_cmd(gputest_impl);


