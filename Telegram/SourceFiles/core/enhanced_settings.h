/*
This file is part of 64Gram Desktop,
the unofficial app based on Telegram Desktop.
For license and copyright information please follow this link:
https://github.com/TDesktop-x64/tdesktop/blob/dev/LEGAL
*/
#pragma once

#include "base/basic_types.h"

#include <QtCore/QByteArray>
#include <QtCore/QTimer>

class PeerData;

namespace EnhancedSettings {

	class Manager : public QObject {
	Q_OBJECT

	public:
		Manager();

		void fill();

		void write(bool force = false);

		void addIdToBlocklist(int64 userId);

		void removeIdFromBlocklist(int64 userId);

	public Q_SLOTS:

		void writeTimeout();

	private:
		void writeDefaultFile();

		void writeCurrentSettings();

		bool readCustomFile();

		void readBlocklist();

		void writing();

		QTimer _jsonWriteTimer;

	};

	void Start();

	void Write();

	void Finish();

	// Local per-peer notes, stored in tdata/peer_notes.json.
	QString PeerNote(uint64 peerId);

	void SetPeerNote(uint64 peerId, const QString &note);

	int PeerNotesRevision();

	QString PeerNotePrefix(not_null<PeerData*> peer);

	// Local chat folders storage, tdata/local_folders_<account>.json.
	QByteArray LocalFoldersJson(uint64 accountId);

	void SetLocalFoldersJson(uint64 accountId, const QByteArray &json);
} // namespace EnhancedSettings
