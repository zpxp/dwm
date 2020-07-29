/* See LICENSE file for copyright and license details. */

/* appearance */

static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int viewontag          = 1;     /* Switch view on tag switch */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int usealtbar          = 1;        /* 1 means use non-dwm status bar */
static const char *altbarclass      = "Polybar"; /* Alternate bar class name */

static const char *fonts[]          = { "Siji:size=10", "Mononoki Nerd Font:size=10:antialias=true:autohint=true" };
static const char dmenufont[]       =  "Mononoki Nerd Font:size=16:antialias=true:autohint=true";
static char col_urgborder[]         = "#ff0000";
static char normbgcolor[]           = "#1d2021";
static char normbordercolor[]       = "#252a30";
static char normfgcolor[]           = "#a9c0c2";
static char selfgcolor[]            = "#83B9C8";
static char selbordercolor[]        = "#83B9C8";
static char selbgcolor[]            = "#303643"; //5ABB55
static char *colors[][3] = {
       /*               fg           bg           border   */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
	[SchemeUrg]  = { selfgcolor, normbgcolor,  col_urgborder  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "11", "12", "13", "14", "15", "16", "17", "18", "19" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Deluge",  NULL,       NULL,       1 << 9,       0,           -1 },
	{ "transmission",  NULL,       NULL,       1 << 9,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int decorhints  = 1;    /* 1 means respect decoration hints */

#include "layouts.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	// { "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|M|",      centeredmaster },
	// { ">M>",      centeredfloatingmaster },
	{ "HHH",      grid },
	{ "[D]",      deck },
	{ "[S]",      spiral },
	{ "TTT",      bstack },
	// { NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      comboview,           {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      combotag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      comboview,           {.ui = 1 << (TAG + 9)} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,           {.ui = 1 << TAG} }, \
	// { MODKEY|ControlMask,           KEY,      toggleview,          {.ui = 1 << TAG} }, \

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "rofi", "-theme", "solarized","-font","siji 10","-show","run", NULL };
// static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *calcmd[]  = { "/bin/sh", "-c", "$HOME/.local/bin/cal", NULL };
static const char *tunescmd[]  = { "st", "ncmpcpp", NULL };

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "normbgcolor",        STRING,  &normbgcolor },
		{ "normbordercolor",    STRING,  &normbordercolor },
		{ "normfgcolor",        STRING,  &normfgcolor },
		{ "selbgcolor",         STRING,  &selbgcolor },
		{ "selbordercolor",     STRING,  &selbordercolor },
		{ "selfgcolor",         STRING,  &selfgcolor },
		{ "borderpx",          	INTEGER, &borderpx },
		{ "snap",          		INTEGER, &snap },
		{ "showbar",          	INTEGER, &showbar },
		{ "topbar",          	INTEGER, &topbar },
		{ "nmaster",          	INTEGER, &nmaster },
		{ "resizehints",       	INTEGER, &resizehints },
		{ "mfact",      	 	FLOAT,   &mfact },
};

#include "selfrestart.c"

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_c,      spawn,          {.v = calcmd } },
	{ MODKEY,                       XK_m,      spawn,          {.v = tunescmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	// { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	// { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_j,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_k,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_Down,   focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_Up,     focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_u,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,            		     XK_comma,  cyclelayout,    {.i = -1 } },
	{ MODKEY,                       XK_period, cyclelayout,    {.i = +1 } },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	// { MODKEY,                       XK_Down,   moveresize,     {.v = "0x 25y 0w 0h" } },
	// { MODKEY,                       XK_Up,     moveresize,     {.v = "0x -25y 0w 0h" } },
	// { MODKEY,                       XK_Right,  moveresize,     {.v = "25x 0y 0w 0h" } },
	// { MODKEY,                       XK_Left,   moveresize,     {.v = "-25x 0y 0w 0h" } },
	// { MODKEY|ShiftMask,             XK_Down,   moveresize,     {.v = "0x 0y 0w 25h" } },
	// { MODKEY|ShiftMask,             XK_Up,     moveresize,     {.v = "0x 0y 0w -25h" } },
	// { MODKEY|ShiftMask,             XK_Right,  moveresize,     {.v = "0x 0y 25w 0h" } },
	// { MODKEY|ShiftMask,             XK_Left,   moveresize,     {.v = "0x 0y -25w 0h" } },
	// { MODKEY|ControlMask,           XK_Up,     moveresizeedge, {.v = "t"} },
	// { MODKEY|ControlMask,           XK_Down,   moveresizeedge, {.v = "b"} },
	// { MODKEY|ControlMask,           XK_Left,   moveresizeedge, {.v = "l"} },
	// { MODKEY|ControlMask,           XK_Right,  moveresizeedge, {.v = "r"} },
	// { MODKEY|ControlMask|ShiftMask, XK_Up,     moveresizeedge, {.v = "T"} },
	// { MODKEY|ControlMask|ShiftMask, XK_Down,   moveresizeedge, {.v = "B"} },
	// { MODKEY|ControlMask|ShiftMask, XK_Left,   moveresizeedge, {.v = "L"} },
	// { MODKEY|ControlMask|ShiftMask, XK_Right,  moveresizeedge, {.v = "R"} },
	{ MODKEY,                       XK_0,      comboview,      {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      combotag,       {.ui = ~0 } },
	{ MODKEY,                       XK_Right,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_Left,   focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Right,  shifttagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Left,   shifttagmon,         {.i = +1 } },
	{ MODKEY|ControlMask,           XK_Right,  tagmon,         {.i = -1 } },
	{ MODKEY|ControlMask,           XK_Left,   tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_equal,      incrgaps,       {.i = +1 } },
	{ MODKEY,                       XK_minus,      incrgaps,       {.i = -1 } },
	{ MODKEY,                       XK_bracketright,      incrogaps,      {.i = +1 } },
	{ MODKEY,                       XK_bracketleft,      incrogaps,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_bracketright,      incrigaps,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_bracketleft,      incrigaps,      {.i = -1 } },
	{ MODKEY|ControlMask,           XK_bracketleft,      togglegaps,     {0} },
	{ MODKEY|ControlMask,           XK_bracketright,      defaultgaps,    {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_e,      quit,           {0} },
	{ MODKEY|ShiftMask,             XK_r,      self_restart,   {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
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

static const char *ipcsockpath = "/tmp/dwm.sock";
static IPCCommand ipccommands[] = {
  IPCCOMMAND(  view,                1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  comboview,                1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  toggleview,          1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  tag,                 1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  combotag,                 1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  toggletag,           1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  tagmon,              1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  focusmon,            1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  focusstack,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  zoom,                1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  spawn,               1,      {ARG_TYPE_PTR}    ),
  IPCCOMMAND(  incnmaster,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  killclient,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  togglefloating,      1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  setmfact,            1,      {ARG_TYPE_FLOAT}  ),
  IPCCOMMAND(  setlayoutsafe,       1,      {ARG_TYPE_PTR}    ),
  IPCCOMMAND(  quit,                1,      {ARG_TYPE_NONE}   )
};
