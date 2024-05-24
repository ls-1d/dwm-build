/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;     /* 0 means no bar */
static const int topbar             = 1;     /* 0 means bottom bar */
static const char *fonts[]          = { "terminus:size=10" };
static const char dmenufont[]       = "terminus:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
    /*               fg         bg         border   */
    [SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
    [SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

typedef struct {
    const char *name;
    const void *cmd;
} Sp;
const char *spcmd1[] = {"urxvtc", "-name", "spterm", NULL };
const char *spcmd2[] = {"urxvtc", "-name", "spncmcpp","-e", "ncmpcpp", NULL };
const char *spcmd3[] = {"urxvtc", "-name", "spchat","-e", "weechat", NULL };
const char *spcmd4[] = {"urxvtc", "-name", "spranger","-e", "ranger", NULL };
static Sp scratchpads[] = {
    /* name          cmd  */
    {"spterm",      spcmd1},
    {"spmusic",     spcmd2},
    {"spweechat",   spcmd3},
    {"spranger",   spcmd4},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const Rule rules[] = {
    /* xprop(1):
     * WM_CLASS(STRING) = instance, class
     * WM_NAME(STRING) = title
     */
      /* class      instance    title       tags mask     isfloating   monitor */
    { "Gimp",		NULL,	NULL,       0,              1,           -1 },
    { "firefox",  	NULL,   NULL,       1 << 6,         0,           -1 },


    { "mpv",        NULL,   NULL,       1 << 1,       False,        -1 },
    { "libreoffice",    NULL,   NULL,       1 << 3,       False,        -1 },
    { "qBittorrent",	NULL,   NULL,       1 << 8,       False,        -1 },


    { NULL,       "spterm",         NULL,       SPTAG(0),       1,           -1 },
    { NULL,       "spncmcpp",       NULL,       SPTAG(1),       1,           -1 },
    { NULL,       "spchat",         NULL,       SPTAG(2),       1,           -1 },
    { NULL,       "spranger",       NULL,       SPTAG(3),       1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
    { "[]=",      tile },    /* first entry is default */
    { "><>",      NULL },    /* no layout function means floating behavior */
    { "[M]",      monocle },
    { "[@]",      spiral },
    { "[\\]",      dwindle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define MODKEY1 Mod1Mask
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "/usr/bin/urxvtc", NULL };
static const char *mutecmd[] = {"amixer","-q","sset","Master","toggle",NULL};
static const char *lowervolcmd[] = {"amixer","-q","sset","Master","1%-",NULL};
static const char *raisevolcmd[] = {"amixer","-q","sset","Master","1%+",NULL};
static const char *brightness_up[]  =   { "xbacklight","-inc", "3", NULL };
static const char *brightness_down[]  = { "xbacklight","-dec", "1", NULL };
static const char *prev_m[]  = { "mpc", "prev", NULL };
static const char *toggle_m[]  = { "mpc", "toggle", NULL };
static const char *next_m[]  = { "mpc", "next", NULL };
static const char *scrotcmd[]  = { "scrot", NULL };

static Key keys[] = {
    /* modifier                     key             function        argument */

    { MODKEY,                       XK_p,           spawn,          {.v = dmenucmd } },
    { MODKEY1,                      XK_Return,      spawn,          {.v = termcmd } },

    // function keys
    { 0,                            0x1008ff16,     spawn,          {.v = prev_m } },
    { 0,                            0x1008ff14,     spawn,          {.v = toggle_m } },
    { 0,                            0x1008ff17,     spawn,          {.v = next_m } },
    { 0,                            0x1008ff02,     spawn,          {.v = brightness_up } },
    { 0,                            0x1008ff03,     spawn,          {.v = brightness_down } },
    { 0,                            0x1008ff12,     spawn,          {.v = mutecmd } },
    { 0,                            0x1008ff11,     spawn,          {.v = lowervolcmd } },
    { 0,                            0x1008ff13,     spawn,          {.v = raisevolcmd } },
    { 0,                            XK_Print,       spawn,          {.v = scrotcmd } },
    { ShiftMask,                    XK_Print,       spawn,          SHCMD("sleep 1s;scrot --select --line mode=edge") },

    // layouts
    { MODKEY,                       XK_t,           setlayout,      {.v = &layouts[0]} },
    { MODKEY|ShiftMask,             XK_t,           setlayout,      {.v = &layouts[1]} },
    { MODKEY,                       XK_m,           setlayout,      {.v = &layouts[2]} },
    { MODKEY,                       XK_r,           setlayout,      {.v = &layouts[3]} },
    { MODKEY|ShiftMask,             XK_r,           setlayout,      {.v = &layouts[4]} },
    { MODKEY,                       XK_space,       setlayout,      {0} },
    { MODKEY|ShiftMask,             XK_space,       togglefloating, {0} },


    { MODKEY,                       XK_b,           togglebar,      {0} },
    { MODKEY,                       XK_j,           focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,           focusstack,     {.i = -1 } },
    { MODKEY,                       XK_i,           incnmaster,     {.i = +1 } },
    { MODKEY,                       XK_d,           incnmaster,     {.i = -1 } },
    { MODKEY,                       XK_h,           setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_l,           setmfact,       {.f = +0.05} },
    { MODKEY,                       XK_Return,      zoom,           {0} },
    { MODKEY,                       XK_Tab,         view,           {0} },
    { MODKEY,                       XK_q,           killclient,     {0} },

    { MODKEY,                       XK_f,           togglefullscr,  {0} },
    { MODKEY,                       XK_0,           view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,           tag,            {.ui = ~0 } },
    { MODKEY,                       XK_comma,       focusmon,       {.i = -1 } },
    { MODKEY,                       XK_period,      focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,             XK_comma,       tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,             XK_period,      tagmon,         {.i = +1 } },

    // scratchpads
    { MODKEY,                       XK_Escape,      togglescratch,  {.ui = 0 } },
    { MODKEY,                       XK_u,           togglescratch,  {.ui = 1 } },
    { MODKEY,                       XK_c,           togglescratch,  {.ui = 2 } },
    { MODKEY,                       XK_x,           togglescratch,  {.ui = 3 } },

    // tags
    TAGKEYS(                        XK_1,                           0)
    TAGKEYS(                        XK_2,                           1)
    TAGKEYS(                        XK_3,                           2)
    TAGKEYS(                        XK_4,                           3)
    TAGKEYS(                        XK_5,                           4)
    TAGKEYS(                        XK_6,                           5)
    TAGKEYS(                        XK_7,                           6)
    TAGKEYS(                        XK_8,                           7)
    TAGKEYS(                        XK_9,                           8)
    { MODKEY|ControlMask,           XK_q,           quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
    { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button1,        resizemouse,    {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

