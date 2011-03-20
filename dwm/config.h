/* See LICENSE file for copyright and license details. */

/* appearance */
#define NUMCOLORS 4 // need at least 3
static const char colors[NUMCOLORS][ColLast][8] = {
   // border   foreground  background
   { "#6699DD", "#FFFFFF", "#222222" },  // 0 = normal
   { "#222222", "#FFFFFF", "#222222" },  // 1 = selected
   { "#E67373", "#FFFFFF", "#E67373" },  // 2 = urgent/warning
   { "#303030", "#FFFFFF", "#4A4A4A" },  // 3 = unselected monitor/dmenu highlight
   // add more here
};
static const char font[]            = "Proggytiny 9";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

/* layout(s) */
static const float mfact        = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster        = 2;    /* default number of clients in the master area */
static const unsigned int gappx = 0;    /* gap pixel between windows */
static const Bool resizehints   = False;/* True means respect size hints in tiled resizals */

#include "nbstack.c"
#include "pidgin_ggrid.c"
#include "gaplessgrid.c"

static const Layout layouts[] = {
	/* symbol add gaps  arrange function */
	{ "=2]",  True,     ntile        },    /* first entry is default */
  	{ "T2T",  True,     nbstack      },
  	{ "[+]",  True,     gaplessgrid  },
	{ "[M]",  False,    monocle      },
  	{ ":++",  True,     pidgin_ggrid },
	{ "><>",  False,    NULL         },    /* no layout function means floating behavior */
};

/* tagging */
static const Tag tags[] = {
  /* name       layout        mfact   nmaster */
  { "Main",     &layouts[1],  -1,     -1 },
  { "Code",     &layouts[0],  -1,     -1 },
  { "Web",      &layouts[1],   0.75,   1 },
  { "IRC",      &layouts[1],   0.15,  -1 },
  { "Chat",     &layouts[5],  -1,     -1 },
  { "Gimp",    	&layouts[0],  -1,     -1 },
  { "Media",  	&layouts[0],  -1      -1 },
  { "Misc",    	&layouts[0],  -1      -1 },
};

/* rules */
static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Chromium", NULL,       NULL,       1 << 2,       False,       -1 },
  	{ "Pidgin",   NULL,       NULL,       1 << 4,       True,        -1 }	,
  	{ "Pidgin",   NULL,       "Pidgin",   1 << 4,       True,        -1 },
  	{ "Vlc",      NULL,       NULL,       1 << 6,       True,        -1 },
	{ "Gimp",     NULL,    	  NULL,	      1 << 5, 	    True,	 -1 },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char dmenufont[] = "Monaco-9";
static const char *dmenucmd[] = { "dmenu_run", 
                                 "-fn", dmenufont, 
                                  "-nb", colors[0][ColBG], 
                                  "-nf", colors[0][ColFG], 
                                  "-sb", colors[3][ColBG], 
                                  "-sf", colors[3][ColFG], 
                                  NULL };
static const char *termcmd[]  = { "urxvtc", NULL };
static const char *webcmd[]   = { "firefox", NULL };
static const char *webcmd2[]  = { "firefox", "-private", NULL };
static const char *devcmd[]   = { "eclipse", NULL };
static const char *imcmd[]    = { "pidgin", NULL };
static const char spadname[]  = "Scratchpad";
static const char *spadcmd[]  = { "urxvtc", 
                                  "-name", spadname, 
                                  "-geometry", "100x25", 
                                  NULL };


#include "push.c"

static Key keys[] = {
	/* modifier                     key        function        argument */
 	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
  { MODKEY,                       XK_w,      spawn,          {.v = webcmd } },
  { MODKEY|ShiftMask,             XK_w,      spawn,          {.v = webcmd2 } },
  { MODKEY,                       XK_d,      spawn,          {.v = devcmd } },
  { MODKEY,                       XK_i,      spawn,          {.v = imcmd } },
  { MODKEY,                       XK_c,      togglespad,     {.v = spadcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
  { MODKEY|ShiftMask,             XK_j,      pushdown,       {0} },
  { MODKEY|ShiftMask,             XK_k,      pushup,         {0} },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
/*{ MODKEY,                       XK_Tab,    view,           {0} }, */
  { MODKEY,                       XK_Tab,    focusstack,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY|ControlMask,           XK_t,      setlayout,      {.v = &layouts[0]} },
  { MODKEY|ControlMask,           XK_s,      setlayout,      {.v = &layouts[1]} },
  { MODKEY|ControlMask,           XK_g,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ControlMask,           XK_m,      setlayout,      {.v = &layouts[3]} },
  { MODKEY|ControlMask,           XK_p,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY|ControlMask,           XK_f,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

