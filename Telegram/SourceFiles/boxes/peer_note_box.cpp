/*
This file is part of 64Gram Desktop,
the unofficial app based on Telegram Desktop.
For license and copyright information please follow this link:
https://github.com/TDesktop-x64/tdesktop/blob/dev/LEGAL
*/
#include "boxes/peer_note_box.h"

#include "core/enhanced_settings.h"
#include "data/data_changes.h"
#include "data/data_peer.h"
#include "lang/lang_keys.h"
#include "main/main_session.h"
#include "ui/boxes/confirm_box.h"
#include "ui/layers/generic_box.h"
#include "ui/widgets/fields/input_field.h"
#include "window/window_session_controller.h"
#include "styles/style_boxes.h"
#include "styles/style_layers.h"

namespace {

constexpr auto kPeerNoteLimit = 30;

} // namespace

void ShowPeerNoteBox(
		not_null<Window::SessionController*> controller,
		not_null<PeerData*> peer) {
	const auto current = EnhancedSettings::PeerNote(peer->id.value);
	controller->uiShow()->showBox(Box([=](not_null<Ui::GenericBox*> box) {
		box->setTitle(tr::lng_peer_note_title());
		box->setWidth(st::boxWidth);

		const auto field = box->addRow(
			object_ptr<Ui::InputField>(
				box,
				st::defaultInputField,
				Ui::InputField::Mode::SingleLine,
				tr::lng_peer_note_placeholder(),
				current),
			st::boxRowPadding);
		field->setMaxLength(kPeerNoteLimit);

		const auto submit = [=] {
			EnhancedSettings::SetPeerNote(
				peer->id.value,
				field->getLastText());
			peer->session().changes().peerUpdated(
				peer,
				Data::PeerUpdate::Flag::Name);
			box->closeBox();
		};
		field->submits() | rpl::on_next(submit, field->lifetime());
		box->addButton(tr::lng_settings_save(), submit);
		box->addButton(tr::lng_cancel(), [=] { box->closeBox(); });
	}));
}
