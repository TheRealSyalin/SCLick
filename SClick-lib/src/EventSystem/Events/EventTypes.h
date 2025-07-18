#pragma once

enum class EventType : unsigned int
{
	None = 0,

	KeyEvent,
	KeyPress,
	KeyRepeat,
	KeyRelease,

	MouseEvent,
	MouseButtonUp,
	MouseButtonDown,
	MouseScroll,
	MouseMove,

	WindowEvent,
	WindowResize,
	WindowDestroy,
	WindowRedraw
};

enum KeyCodes : unsigned short
{
	ENTER = 13, BACKSPACE, ESCAPE, TAB, CAPLK, FN, SPECIAL,

	SHIFT, CRTL, ALT, RSHIFT, RCTRL, RALT,

	F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,F11,F12,

	LARROW, RARROW, DARROW, UARROW,

	A = 65 ,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,

	a = 97 ,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z
};

enum MouseButtons : unsigned char
{
	LMOUSE = 'L', RMOUSE = 'R', MMOUSE = 'M'
};
