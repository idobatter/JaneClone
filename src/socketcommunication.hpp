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

#ifndef SOCKETCOMMUNICATION_HPP_
#define SOCKETCOMMUNICATION_HPP_

#include <sstream>
#include <iostream>

#include <wx/wx.h>
#include <wx/string.h>
#include <wx/filefn.h>
#include <wx/filename.h>
#include <wx/textfile.h>
#include <wx/protocol/http.h>
#include <wx/protocol/protocol.h>
#include <wx/wfstream.h>
#include <wx/datstrm.h>
#include <wx/regex.h>
#include <wx/dir.h>
#include <wx/utils.h>
#include <wx/config.h>
#include <wx/fileconf.h>
#include <wx/sstream.h>
#include <wx/sckstrm.h>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Infos.hpp>

#include "enums.hpp"
#include "janecloneutil.hpp"
#include "sqliteaccessor.hpp"

class SocketCommunication {


public:

     /**
      * コンストラクタ
      */
     SocketCommunication(){
	  this->respBuf.clear();
	  this->bodyBuf.clear();
     };
     /**
      * デストラクタ
      */
     ~SocketCommunication();
     /**
      * 板一覧ファイルをダウンロードしてくるメソッド
      * もし前回通信した際のログが残っていれば更新の確認のみ行う
      * @param  板一覧datファイル保存先
      * @param  板一覧headerファイル保存先
      * @return 実行コード
      */
     int DownloadBoardList(const wxString outputPath, const wxString headerPath);
     /**
      * スレッド一覧をダウンロードしてくるメソッド
      * @param 板名
      * @param URL
      * @param サーバー名
      * @return ダウンロードしたdatファイル保存先
      */
     wxString DownloadThreadList(const wxString boardName,
				 const wxString boardURL, const wxString boardNameAscii);
     /**
      * スレッドのデータをダウンロードしてくるメソッド
      * @param 板名
      * @param URL
      * @param サーバー名
      * @param 固有番号
      * @return ダウンロードしたdatファイル保存先
      */
     wxString DownloadThread(const wxString boardName, const wxString boardURL,
			     const wxString boardNameAscii, const wxString origNumber);

#ifdef USE_SHINGETSU
     /**
      * 新月のスレッドをダウンロードしてくるメソッド
      * @param  公開ノードのURL
      * @param  ファイル名
      * @return ダウンロードしたcsvファイルの保存先
      */
     wxString DownloadShingetsuThread(const wxString& nodeHostname, 
				      const wxString& title, const wxString& filename);
#endif /** USE_SHINGETSU */

     /**
      * スレッドへの初回書き込みを行うメソッド
      * @param 板名,URL,サーバー名
      * @return 書き込み結果
      */
     wxString PostFirstToThread(URLvsBoardName& boardInfoHash, ThreadInfo& threadInfoHash, const int status);
     /**
      * 投稿確認ボタンイベントの後にスレッドに書き込むメソッド
      * @param 板名,URL,サーバー名
      * @return 書き込み結果
      */
     wxString PostConfirmToThread(URLvsBoardName& boardInfoHash, ThreadInfo& threadInfoHash, const int status);
     /**
      * 通常の書き込みメソッド
      * @param 板名,URL,サーバー名
      * @return 書き込み結果
      */
     wxString PostResponseToThread(URLvsBoardName& boardInfoHash, ThreadInfo& threadInfoHash, const int status);

     /**
      * 投稿内容をソケット通信クラスに設定する
      * @param PostContent構造体
      */
     void SetPostContent(PostContent* postContent);
     /**
      * 指定されたURLからデータをダウンロードする
      */
     void DownloadImageFile(const wxString& href, DownloadImageResult* result);
     /**
      * HTTPでのダウンロード
      */
     void DownloadImageFileByHttp(const wxString& href, DownloadImageResult* result);
     /**
      * FTPでのダウンロード
      */
     void DownloadImageFileByFtp(const wxString& href, DownloadImageResult* result);
     /**
      * したらば掲示板の情報を取得する
      */
     bool GetShitarabaBoardInfo(const wxString& path, wxString& boardName, wxString& category);

#ifdef USE_SHINGETSU
     /**
      * 新月の公開ノードからスレッド一覧を取得する
      */
     bool DownloadShingetsuThreadList(const wxString& nodeHostname, wxString& outputFilePath);
#endif /** USE_SHINGETSU */

private:

     // メインのスレッドにログとイベントを送る
     void SendLogging(wxString& message) {
	  wxCommandEvent* event = new wxCommandEvent(wxEVT_COMMAND_TEXT_UPDATED, ID_Logging);
	  event->SetString(message.c_str());

#if wxCHECK_VERSION(2, 9, 0)
	  wxTheApp->GetTopWindow()->GetEventHandler()->QueueEvent(event->Clone());
#else
	  wxTheApp->GetTopWindow()->GetEventHandler()->AddPendingEvent(*event);
#endif
     };

     /**
      * ファイル区切り文字
      */
     inline char separator() {
#ifdef __WXMSW__
	  return '\\';
#else
	  return '/';
#endif
     };
     /**
      * ヘッダファイル情報
      */
     std::string respBuf;
     /**
      * HTTPの本文の情報
      */
     std::string bodyBuf;
     /**
      * 新規に板一覧情報を取得しに行く
      */
     int DownloadBoardListNew(const wxString outputPath,
			      const wxString headerPath);
     /**
      * 前回との差分を取得しに行く
      */
     int DownloadBoardListMod(const wxString outputPath,
			      const wxString headerPath);
     /**
      * 新規にスレッド一覧をダウンロードしてくるメソッド
      * @param gzipのダウンロード先パス
      * @param HTTPヘッダのダウンロード先パス
      * @param 板名（ascii）
      * @return 実行コード
      */
     int DownloadThreadListNew(const wxString gzipPath,
			       const wxString headerPath, const wxString boardNameAscii,
			       const wxString hostName, const wxString boardURL);
     /**
      * 前回との差分のスレッド一覧をダウンロードしてくるメソッド
      * @param gzipのダウンロード先パス
      * @param HTTPヘッダのダウンロード先パス
      * @param 板名（ascii）
      * @return 実行コード
      */
     int DownloadThreadListMod(const wxString gzipPath,
			       const wxString headerPath, const wxString boardNameAscii,
			       const wxString hostName, const wxString boardURL);

     /**
      * 新規にスレッドのデータをダウンロードしてくるメソッド
      * @param gzipのダウンロード先パス
      * @param HTTPヘッダのダウンロード先パス
      * @param 板名（ascii）
      * @param 固有番号
      * @param サーバーのホスト名
      * @return 実行コード
      */
     void DownloadThreadNew(const wxString gzipPath, const wxString headerPath,
			    const wxString boardNameAscii, const wxString origNumber,
			    const wxString hostName);

     /**
      * 前回との差分のスレッドのデータをダウンロードしてくるメソッド
      * @param gzipのダウンロード先パス
      * @param HTTPヘッダのダウンロード先パス
      * @param 板名（ascii）
      * @param 固有番号
      * @param サーバーのホスト名
      * @return 実行コード
      */
     int DownloadThreadMod(const wxString gzipPath, const wxString headerPath,
			   const wxString boardNameAscii, const wxString origNumber,
			   const wxString hostName);

     /**
      * 過去のスレッドのデータをダウンロードしてくるメソッド
      * @param gzipのダウンロード先パス
      * @param HTTPヘッダのダウンロード先パス
      * @param 板名（ascii）
      * @param 固有番号
      * @param サーバーのホスト名
      * @return 実行コード
      */
     int DownloadThreadPast(const wxString gzipPath, const wxString headerPath,
			    const wxString boardNameAscii, const wxString origNumber,
			    const wxString hostName, const wxString ext = wxT(".dat.gz"));     

     /**
      * 通信ログに残っているHTTPレスポンスコードを取得する
      */
     wxString GetHTTPResponseCode(const wxString headerPath, const wxString reqCode);
     /**
      * 一時ファイルを消す
      */
     void RemoveTmpFile(const wxString removeFile);
     /**
      * HTTPヘッダを書きだす
      */
     size_t WriteHeaderData(char *ptr, size_t size, size_t nmemb);
     /**
      * HTTPボディを書きだす
      */
     size_t WriteDataInternal(char *ptr, size_t size, size_t nmemb);
     /**
      * COOKIE関連の初期化処理を行う
      */
     void InitializeCookie();
     /**
      * COOKIE文字列の連結処理を行う
      */
     void AssembleCookie(wxString& cookie, const wxString& hiddenName, const wxString& hiddenVal);
     /**
      * COOKIE文字列の切り出し処理を行う
      */
     void SubstringCookie(wxString& cookie) {
	  if (cookie.Len() > 0) {
	       cookie = cookie.Mid(0, cookie.Find(wxT(";")));
	  }
     };
     /**
      * COOKIEのデータ書き出しを行う
      */
     void WriteCookieData(const wxString& dataFilePath);
     // wxFileConfigクラスのインスタンス(書き込みの際のみ確保される)
     wxFileConfig* config;
     // 投稿内容を保存するクラス(書き込みの際のみ確保される)
     PostContent* postContent;

     /**
      * ダウンロードした画像ファイル情報をDBに格納する
      */
     void SaveImageFileInfoDB(const wxString& href, DownloadImageResult* result);
     /**
      * BE２ちゃんねるにログインしてプロパティファイルに情報を書き出す
      */
     void LoginBe2ch();
};

#endif /* SOCKETCOMMUNICATION_HPP_ */
