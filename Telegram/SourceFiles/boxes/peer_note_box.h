/*
This file is part of 64Gram Desktop,
the unofficial app based on Telegram Desktop.
For license and copyright information please follow this link:
https://github.com/TDesktop-x64/tdesktop/blob/dev/LEGAL
*/
#pragma once

#include "base/basic_types.h"

class PeerData;

namespace Window {
class SessionController;
} // namespace Window

void ShowPeerNoteBox(
	not_null<Window::SessionController*> controller,
	not_null<PeerData*> peer);
