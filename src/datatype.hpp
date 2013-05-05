/* JaneClone - a text board site viewer for 2ch
 * Copyright (C) 2012 Hiroyuki Nagata
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * Contributor:
 *	Hiroyuki Nagata <newserver002@gmail.com>
 */

#ifndef DATATYPE_HPP_
#define DATATYPE_HPP_

#include <wx/regex.h>

/*
 * 定数値の宣言
 */
/** JaneClone公式サイトのURL */
#define JANECLONE_DOWNLOADSITE wxT("http://hiroyuki-nagata.github.io/")
/** JaneCloneの作業用隠しフォルダ名 */
#define JANECLONE_DIR wxT(".jc")
/** wxAuiToolbarを使うかどうか */
#define USE_WXAUITOOLBAR 1
/** コンフィグファイル名 */
#define APP_CONFIG_FILE wxT("janeclone.env")

// ファイルの区切り文字
#ifdef __WXMSW__
  #define wxFileSeparator wxT("\\") 
#else
  #define wxFileSeparator wxT("/") 
#endif

// 実行ファイルの拡張子
#ifdef __WXMSW__
  #define wxExt wxT(".exe") 
#else
  #define wxExt wxT("") 
#endif

// 板一覧情報ファイルのパス
#define BOARD_LIST_PATH ::wxGetHomeDir() + wxFileSeparator + JANECLONE_DIR + wxFileSeparator + wxT("dat") + wxFileSeparator + wxT("boardlist.html")
// 板一覧情報ファイルのヘッダ情報のパス
#define BOARD_LIST_HEADER_PATH ::wxGetHomeDir() + wxFileSeparator + JANECLONE_DIR + wxFileSeparator + wxT("dat") + wxFileSeparator + wxT("boardlistheader.html")

/** 各ウィジェットの名前を表す定数値 */
#define JANECLONE_WINDOW       wxT("janeclone_window")
#define SEARCH_BAR             wxT("m_search_ctrl")
#define URL_BAR                wxT("m_url_input_panel")
#define BOARD_TREE             wxT("m_tree_ctrl")
#define LOG_WINDOW             wxT("m_logCtrl")
#define BOARD_NOTEBOOK         wxT("boardNoteBook")
#define THREAD_NOTEBOOK        wxT("threadNoteBook")

/**
 * クラス
 */

// 2chの板名とURLを対応させるクラス
class URLvsBoardName {
public:
     wxString boardName;
     wxString boardURL;
     wxString boardNameAscii;
};

// スレッド一覧用のクラス
class ThreadList {
public:
     // キー値(ホスト名にこの番号をつけることでスレッドのURLになる)
     wxString oid;
     // 番号(単に取得したdatファイルの順序から)
     int number;
     // タイトル
     wxString title;
     // レス
     int response;
     // 取得
     int cachedResponseNumber;
     // 新着
     int newResponseNumber;
     // 増レス
     int increaseResponseNumber;
     // 勢い
     int momentum;
     // 最終取得
     wxString lastUpdate;
     // since
     wxString since;
     // 板
     wxString boardName;
};

// 2chの板名(ascii)と固有番号を対応させて保存するクラス
class ThreadInfo {
public:
     // スレッドタイトル
     wxString title;
     // スレッド固有番号
     wxString origNumber;
     // 板名(英数)
     wxString boardNameAscii;
};

/**
 * 構造体
 */

// 書き込みを行う際の投稿内容
typedef struct {
     wxString name;
     wxString mail;
     wxString kakikomi;
} PostContent;

// 画像をダウンロードした後の結果
typedef struct {
     wxString imagePath; // 画像ファイルのパス
     wxString imageURL;  // 画像ファイルのURL
     wxString ext;       // 画像ファイルの拡張子
     bool     result;    // 取得の成否
} DownloadImageResult;

// URIを分解した時の各要素
typedef struct {
     wxString protocol;
     wxString hostname;
     wxString port;
     wxString path;
} PartOfURI;

/**
 * 変数
 */

// ヘッダ部分にあたるHTML
static const wxString HTML_HEADER =
		wxT("<html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"></head><body bgcolor=#efefef text=black link=blue alink=red vlink=#660099>");

// ポップアップウィンドウのヘッダ部分にあたるHTML
static const wxString HTML_HEADER_POPUP =
		wxT("<html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"></head><body bgcolor=#eedcb3 text=black link=blue alink=red vlink=#660099>");

// 投稿失敗時のHTML
static const wxString FAIL_TO_POST = wxT("<html><head><meta http-equiv=\"Content-Type\" content=\"text/html; \
			charset=UTF-8\"><title></title></head><body><span>レスの投稿に失敗しました</span></body></html>");

// フッター部分にあたるHTML
static const wxString HTML_FOOTER = wxT("</body></html>");

// スレッドの１番目を読み込む正規表現
static const wxRegEx regexThreadFst(_T("^(.+)<>(.*)<>(.+)<>(.*)<>(.+)"), wxRE_ADVANCED + wxRE_ICASE);

// スレッド読み込み用正規表現
static const wxRegEx regexThread(_T("^(.+)<>(.*)<>(.+)<>(.*)<>$"), wxRE_ADVANCED + wxRE_ICASE);

// URL検出用正規表現
static const wxRegEx regexURL(_T("(http|https|ttp|ftp)://([[:alnum:]]|[[:punct:]]|[=]|[~]|[+])*"), wxRE_ADVANCED + wxRE_ICASE);

// 画像リンク検出用正規表現
static const wxRegEx regexImage(_T("(http|https|ttp|ftp)://([[:alnum:]]|[[:punct:]]|[=]|[~]|[+])*.(jpg|jpeg|png|gif|bmp)"), wxRE_ADVANCED + wxRE_ICASE);

// URIマッチング用正規表現
static const wxRegEx regexURI(_T("(http|https|ttp|ftp)://([-0-9a-zA-Z\\._]*)(:[0-9]+)?([-/\\.a-zA-Z0-9_#~:.?+=&%!@]*)"), wxRE_ADVANCED + wxRE_ICASE);

#endif /* DATATYPE_HPP_ */
