
/* appearance */
static const unsigned int borderpx            = 3;   /* border pixel of windows */
static const unsigned int snap                = 32;  /* snap pixel */
static const unsigned int systraypinning      = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor */
static const unsigned int systrayonleft       = 0;   /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing      = 1;   /* systray spacing */
static const int systraypinningfailfirst      = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor */
static const int showsystray                  = 1;   /* 0 means no systray */
static const int showbar                      = 1;   /* 0 means no bar */
static const int topbar                       = 1;   /* 0 means bottom bar */
static const unsigned int gappih              = 5;   /* horiz inner gap between windows */
static const unsigned int gappiv              = 5;   /* vert inner gap between windows */
static const unsigned int gappoh              = 5;   /* horiz outer gap between windows and screen edge */
static const unsigned int gappov              = 5;   /* vert outer gap between windows and screen edge */
static int smartgaps                          = 0;   /* 1 means no outer gap when there is only one window */
static const char *fonts[]                    = { "Maple Mono:size=14", "Noto Color Emoji:size=13", "CoconNextArabic-Light:size=13" };
static const char dmenufont[]                 = "Maple Mono:size=15";
static const char col1[]                      = "#ffffff";
static const char col2[]                      = "#ffffff";
static const char col3[]                      = "#ffffff";
static const char col4[]                      = "#ffffff";
static const char col5[]                      = "#ffffff";
static const char col6[]                      = "#ffffff";
static const char col_gray1[]                 = "#181825";
static const char col_gray2[]                 = "#6C6990";
static const char col_gray3[]                 = "#6C6990";
static const char col_gray4[]                 = "#1E1D2D";
static const char col_cyan[]                  = "#282737";
static const char col_black[]                 = "#1E1D2D";
static const char col_blue[]                  = "#96CDFB"; /* focused window border */
static const char col_green[]                 = "#ABE9B3";
static const char col_accent[]                = "#94E2D5";
static const char col_orange[]                = "#F8BD96";
static const char col_yellow[]                = "#FAE3B0";
static const char col_teal[]                  = "#94E2D5";
static const char col_sapphire[]              = "#89B4FA";
static const char col_blu[]                   = "#008080";
static const char col_borderbar[]             = "#1E1D2D"; /* inner border */

static const char *colors[][3] = {
    /*               fg         bg         border   */
    [SchemeNorm] = { col_accent, col_gray1, col_gray2 },
    [SchemeSel]  = { col_accent, col_black, col_accent },
};

/* tagging */
static const char *tags[] = {  "", "", "", "", "󱍑", "", "󰮤", "󱍑", "󰒱" };

static const Rule rules[] = {
    /* class                instance    title       tags mask     isfloating   monitor */
    { "Peek",               NULL,       NULL,       0,            1,           -1 },
    { "peek",               NULL,       NULL,       0,            1,           -1 },
    { "copyq",              NULL,       NULL,       0,            1,           -1 },
    { "Slack",              NULL,       NULL,       1 << 8,       0,           -1 },
    { "telegram-desktop",   NULL,       NULL,       1 << 7,       0,           -1 },
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster       = 1;    /* number of clients in master area */
static const int resizehints   = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1;   /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1 /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[]=",      tile },    /* first entry is default */
    { "><>",      NULL },    /* no layout function means floating behavior */
    { "[M]",      monocle },
    { "[@]",      spiral },
    { "[\\]",     dwindle },
    { "H[]",      deck },
    { "TTT",      bstack },
    { "===",      bstackhoriz },
    { "HHH",      grid },
    { "###",      nrowgrid },
    { "---",      horizgrid },
    { ":::",      gaplessgrid },
    { "|M|",      centeredmaster },
    { ">M>",      centeredfloatingmaster },
    { NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG) \
    { MODKEY,                       KEY, view,        {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY, toggleview,  {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY, tag,         {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY, toggletag,   {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) \
    { .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_accent, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

#include "movestack.c"
static const Key keys[] = {
    /* modifier                     key            function        argument */
    { MODKEY,                       XK_d,          spawn,          {.v = dmenucmd } },
    { MODKEY,                       XK_Return,     spawn,          {.v = termcmd } },
    { MODKEY,                       XK_b,          togglebar,      {0} },
    { MODKEY,                       XK_j,          focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,          focusstack,     {.i = -1 } },
    { MODKEY,                       XK_h,          setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_l,          setmfact,       {.f = +0.05} },
    { MODKEY,                       XK_i,          view_adjacent,  {.i = +1 } },
    { MODKEY,                       XK_u,          view_adjacent,  {.i = -1 } },
    { MODKEY|ShiftMask,             XK_h,          setcfact,       {.f = +0.25} },
    { MODKEY|ShiftMask,             XK_l,          setcfact,       {.f = -0.25} },
    { MODKEY|ShiftMask,             XK_o,          setcfact,       {.f = 0.00} },
    { MODKEY|ShiftMask,             XK_Return,     zoom,           {0} },
    { MODKEY|Mod1Mask,              XK_u,          incrgaps,       {.i = +1 } },
    { MODKEY|Mod1Mask|ShiftMask,    XK_u,          incrgaps,       {.i = -1 } },
    { MODKEY|Mod1Mask,              XK_i,          incrigaps,      {.i = +1 } },
    { MODKEY|Mod1Mask|ShiftMask,    XK_i,          incrigaps,      {.i = -1 } },
    { MODKEY|Mod1Mask,              XK_o,          incrogaps,      {.i = +1 } },
    { MODKEY|Mod1Mask|ShiftMask,    XK_o,          incrogaps,      {.i = -1 } },
    { MODKEY|Mod1Mask,              XK_6,          incrihgaps,     {.i = +1 } },
    { MODKEY|Mod1Mask|ShiftMask,    XK_6,          incrihgaps,     {.i = -1 } },
    { MODKEY|Mod1Mask,              XK_7,          incrivgaps,     {.i = +1 } },
    { MODKEY|Mod1Mask|ShiftMask,    XK_7,          incrivgaps,     {.i = -1 } },
    { MODKEY|Mod1Mask,              XK_8,          incrohgaps,     {.i = +1 } },
    { MODKEY|Mod1Mask|ShiftMask,    XK_8,          incrohgaps,     {.i = -1 } },
    { MODKEY|Mod1Mask,              XK_9,          incrovgaps,     {.i = +1 } },
    { MODKEY|Mod1Mask|ShiftMask,    XK_9,          incrovgaps,     {.i = -1 } },
    { MODKEY|Mod1Mask,              XK_0,          togglegaps,     {0} },
    { MODKEY|Mod1Mask|ShiftMask,    XK_0,          defaultgaps,    {0} },
    { MODKEY,                       XK_Tab,        view,           {0} },
    { MODKEY|ShiftMask,             XK_q,          killclient,     {0} },
    { MODKEY,                       XK_t,          setlayout,      {.v = &layouts[0]} },
    { MODKEY,                       XK_f,          fullscreen,     {0} },
    { MODKEY|ShiftMask,             XK_j,          movestack,      {.i = +1 } },
    { MODKEY|ShiftMask,             XK_k,          movestack,      {.i = -1 } },
    { MODKEY,                       XK_space,      setlayout,      {0} },
    { MODKEY|ShiftMask,             XK_space,      togglefloating, {0} },
    { MODKEY,                       XK_0,          view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,          tag,            {.ui = ~0 } },
    { MODKEY,                       XK_comma,      focusmon,       {.i = -1 } },
    { MODKEY,                       XK_period,     focusmon,       {.i = +1 } },
    { MODKEY|Mod1Mask,              XK_comma,      incnmaster,     {.i = +1 } },
    { MODKEY|Mod1Mask,              XK_period,     incnmaster,     {.i = -1 } },
    { MODKEY|ShiftMask,             XK_comma,      tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,             XK_period,     tagmon,         {.i = +1 } },
    { MODKEY|ControlMask,           XK_comma,      cyclelayout,    {.i = -1 } },
    { MODKEY|ControlMask,           XK_period,     cyclelayout,    {.i = +1 } },
    TAGKEYS(                        XK_1,                          0)
    TAGKEYS(                        XK_2,                          1)
    TAGKEYS(                        XK_3,                          2)
    TAGKEYS(                        XK_4,                          3)
    TAGKEYS(                        XK_5,                          4)
    TAGKEYS(                        XK_6,                          5)
    TAGKEYS(                        XK_7,                          6)
    TAGKEYS(                        XK_8,                          7)
    TAGKEYS(                        XK_9,                          8)
    { MODKEY|ShiftMask,             XK_c,          quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
    { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
    { ClkTagBar,            0,              Button4,        view_adjacent,  { .i = -1 } },
    { ClkTagBar,            0,              Button5,        view_adjacent,  { .i = +1 } },
};

