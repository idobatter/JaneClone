// -*- C++ -*- generated by wxGlade 0.6.3 on Tue Nov 01 01:42:24 2011

#include "JaneClone.h"

using namespace std;

// enum
enum {
	ID_Quit = 1, ID_About, ID_GetBoardList, ID_GetVersionInfo, ID_AnyRightClick
};

// event table
BEGIN_EVENT_TABLE(JaneClone, wxFrame)

// メニューバーにあるコマンド入力で起動するメソッドのイベントテーブル
EVT_MENU(ID_Quit, JaneClone::OnQuit)
EVT_MENU(ID_About, JaneClone::OnAbout)
EVT_MENU(ID_GetBoardList, JaneClone::OnGetBoardList)
EVT_MENU(ID_GetVersionInfo, JaneClone::OnVersionInfo)

// ツリーコントロールのイベント
EVT_TREE_SEL_CHANGED(wxID_ANY, JaneClone::OnGetBoardInfo)

// 右クリックした際のイベント処理
EVT_CONTEXT_MENU(JaneClone::OnContext)
EVT_AUINOTEBOOK_TAB_RIGHT_DOWN(wxID_ANY, JaneClone::OnRightClick)

// 終了前処理
EVT_CLOSE(JaneClone::OnCloseWindow)

END_EVENT_TABLE()

JaneClone::JaneClone(wxWindow* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
wxFrame(parent, id, title, pos, size, wxDEFAULT_FRAME_STYLE)
{
	// アイコンの設定
	SetIcon(wxICON(wxicon));
	// メニューバーの設置
	wxMenuBar *menuBar = new wxMenuBar;
	wxMenu *menu1 = new wxMenu;
	menu1->Append(ID_About, wxT("このソフトについて..."));
	menu1->Append(ID_Quit, wxT("終了"));
	wxMenu *menu2 = new wxMenu;
	wxMenu *menu3 = new wxMenu;
	menu3->Append(ID_GetBoardList, wxT("板一覧更新"));
	wxMenu *menu4 = new wxMenu;
	wxMenu *menu5 = new wxMenu;
	wxMenu *menu6 = new wxMenu;
	wxMenu *menu7 = new wxMenu;
	wxMenu *menu8 = new wxMenu;
	wxMenu *menu9 = new wxMenu;
	menu9->Append(ID_GetVersionInfo, wxT("バージョン情報を開く"));
	menuBar->Append(menu1, wxT("ファイル"));
	menuBar->Append(menu2, wxT("表示"));
	menuBar->Append(menu3, wxT("板一覧"));
	menuBar->Append(menu4, wxT("スレッド一覧"));
	menuBar->Append(menu5, wxT("お気に入り"));
	menuBar->Append(menu6, wxT("検索"));
	menuBar->Append(menu7, wxT("ウィンドウ"));
	menuBar->Append(menu8, wxT("ツール"));
	menuBar->Append(menu9, wxT("ヘルプ"));

	SetMenuBar(menuBar);// メニューバー設置終わり

	// SetMinimumPaneSizeによってペインが合体しないように設定
	window_1 = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D|wxSP_BORDER);
	window_1->SetMinimumPaneSize(20);
	window_1_pane_2 = new wxPanel(window_1, wxID_ANY);
	window_1_pane_1 = new wxPanel(window_1, wxID_ANY);

	window_2 = new wxSplitterWindow(window_1_pane_2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D|wxSP_BORDER);
	window_2->SetMinimumPaneSize(20);

	//URL入力欄の表示部分
	label_1 = new wxStaticText(this, wxID_ANY, wxT("URL:"));
	textCtlForURL = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
	button_1 = new wxButton(this, wxID_ANY, wxT("GO"));

	//板一覧を取得してツリー表示
	m_tree_ctrl = new wxTreeCtrl(window_1_pane_1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_HAS_BUTTONS|wxTR_DEFAULT_STYLE|wxSUNKEN_BORDER);
	window_2_pane_1 = new wxPanel(window_2, wxID_ANY);
	window_2_pane_2 = new wxPanel(window_2, wxID_ANY);

	// 呼ばれる順序はSetProperties　→　DoLayout
	SetProperties();
	DoLayout();
	this->CreateStatusBar();
	this->SetStatusText(wxT(" 完了"));
}

/**
 * SetProperties
 * 前回からのデータ引継ぎ等の処理を行う。
 *
 */
void JaneClone::SetProperties() {
	// wxGladeによる自動生成
	SetTitle(_("JaneClone"));
	SetSize(wxSize(960, 540));
	label_1->SetFont(
			wxFont(9, wxDEFAULT, wxNORMAL, wxNORMAL, 0, wxT("MS Shell Dlg 2")));

	// 板一覧情報を反映する
	wxImageList *treeImage = new wxImageList(16, 16);
	wxBitmap idx1 = wxArtProvider::GetBitmap(wxART_FOLDER, wxART_OTHER);
	wxBitmap idx2 = wxArtProvider::GetBitmap(wxART_NEW, wxART_OTHER);
	treeImage->Add(idx1);
	treeImage->Add(idx2);
	m_tree_ctrl->AssignImageList(treeImage);

	// 板一覧情報のツリーコントロール
	m_treeData = new wxTreeItemData();
	m_rootId = m_tree_ctrl->AddRoot(wxT("2ch板一覧"), 0, 0, m_treeData);

	// カレントディレクトリを設定
	wxDir dir(wxGetCwd());
	// datフォルダ、propフォルダが存在するか確認。無ければ確認＆フォルダを作成
	if (!dir.Exists(wxT("./dat/"))) {
		wxMessageBox(wxT("datデータ保存用ディレクトリが見当たらないので作成します。\nフォルダ構成を確認してください。"));
		::wxMkdir(wxT("./dat/"));
	}
	if (!dir.Exists(wxT("./prop/"))) {
		wxMessageBox(wxT("設定ファイル保存用ディレクトリが見当たらないので作成します。\nフォルダ構成を確認してください。"));
		::wxMkdir(wxT("./prop/"));
	}
	// もし板一覧ファイルがdatフォルダに存在するならば一気に板一覧設定に飛ぶ
	if (wxFile::Exists(wxT("./dat/BoardListUTF8.html"))) {
		JaneClone::SetBoardList();
	}
	// wxAuiNotebookに更新した
	boardNoteBook = new wxAuiNotebook(window_2_pane_1, wxID_ANY,
			wxDefaultPosition, wxDefaultSize, wxAUI_NB_DEFAULT_STYLE);
}

/**
 * DoLayout
 * ユーザーが触る前のアプリのレイアウトを設定する
 * 前回の起動時にレイアウトに変更があった場合はそれを反映する
 */

void JaneClone::DoLayout() {
	// 各種サイザー設定
	wxBoxSizer* sizer_1 = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* sizer_2 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* sizer_3 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* sizer_4 = new wxBoxSizer(wxHORIZONTAL);

	// 一番上のURL入力欄など
	sizer_2->Add(label_1, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL,
			0);
	sizer_2->Add(textCtlForURL, 2, wxALL | wxEXPAND, 0);
	sizer_2->Add(button_1, 0, 0, 0);
	sizer_1->Add(sizer_2, 0, wxALL | wxEXPAND, 2);

	// 下部のスプリットウィンドウの設定
	// Sizer3にツリーコントロールが入る
	sizer_3->Add(m_tree_ctrl, 1, wxEXPAND, 0);
	window_1_pane_1->SetSizer(sizer_3);

	// スプリットウィンドウ(横の区切り)
	window_2->SplitHorizontally(window_2_pane_1, window_2_pane_2);
	sizer_4->Add(window_2, 1, wxEXPAND, 0);
	window_1_pane_2->SetSizer(sizer_4);

	// スプリットウィンドウ(縦の区切り)
	window_1->SplitVertically(window_1_pane_1, window_1_pane_2);
	sizer_1->Add(window_1, 1, wxEXPAND, 0);
	SetSizer(sizer_1);

	// datフォルダ内にあるスレッド一覧の情報が入ったファイルとプロパティファイルを比べて
	// 右側のペインにスレッド一覧情報を反映する

	// 初期設定はこのLayout()が呼ばれる前に行わなくてはいけない
	Layout();
	// end wxGlade
}

void JaneClone::OnQuit(wxCommandEvent&) {

	// ツリーコントロールをデリートしてやらないとセグる
	delete m_tree_ctrl;
	Close(true);
}

void JaneClone::OnAbout(wxCommandEvent&) {
}

// 板一覧のツリーがクリックされたときに起きるイベント
void JaneClone::OnGetBoardInfo(wxTreeEvent& event) {
	// 選択されたTreeItemIdのインスタンス
	wxTreeItemId pushedTree = event.GetItem();

	// もし選択されたツリーが板名だったら(※TreeItemに子要素が無かったら)
	if (!m_tree_ctrl->ItemHasChildren(pushedTree)) {
		// 板名をwxStringで取得する
		wxString boardName = m_tree_ctrl->GetItemText(pushedTree);
		// URLを保持する文字列
		wxString boardURL;
		// 板名に対応したURLを取ってくる
		NameURLHash::iterator it;
		for (it = retainHash.begin(); it != retainHash.end(); ++it) {
			URLvsBoardName* hash = it->second;
			if (hash->BoardName.Cmp(boardName) == 0) {
				boardURL = hash->BoardURL;
				break;
			}
		}
		// 板一覧のツリーをクリックして、それをノートブックに反映するメソッド
		SetBoardNameToNoteBook(boardName, boardURL);
	}
}

// 板一覧のツリーをクリックして、それをノートブックに反映するメソッド
void JaneClone::SetBoardNameToNoteBook(wxString& boardName,
		wxString& boardURL) {
	// 戻り値は出力したgzipファイルの保存先
	wxString outputPath = DownloadThreadList(boardURL);
	// 出力先を指定してgzipファイルを解凍
	wxString inputDecommPath = outputPath;
	wxString outputDecommPath = outputPath;
	outputDecommPath.Replace(_T(".gzip"), _T(".tmp"));

	JaneClone::DecommpressFile(inputDecommPath, outputDecommPath);
	// 出力先を指定してSJISのファイルをエンコードしてUTF-8に変える
	wxString inputConvPath = outputDecommPath;
	wxString outputConvPath = outputDecommPath;
	outputConvPath.Replace(_T(".tmp"), _T(".dat"));
	JaneClone::ConvertSJISToUTF8(inputConvPath, outputConvPath);

	// 更新が終わったらgzipファイルとSJISファイルを消しておく
	if (wxFile::Exists(inputDecommPath) && wxFile::Exists(outputDecommPath)) {
		wxRemoveFile(inputDecommPath);
		wxRemoveFile(outputDecommPath);
	}
	// NoteWindow上にはwxListCtrlが乗る予定
	wxPanel *noteWindow = new wxPanel(boardNoteBook, wxID_ANY);
	wxBoxSizer* sizer_noteList = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* sizer_pane = new wxBoxSizer(wxVERTICAL);
	wxListCtrl* threadList = new wxListCtrl(noteWindow, wxID_ANY,
			wxDefaultPosition, wxDefaultSize, wxLC_REPORT);

	/** スレッド一覧画面用の材料を生成　*/
	sizer_noteList->Add(threadList, 1, wxEXPAND, 0);
	noteWindow->SetSizer(sizer_noteList);
	boardNoteBook->AddPage(noteWindow, boardName);
	sizer_pane->Add(boardNoteBook, 1, wxEXPAND, 0);
	window_2_pane_1->SetSizer(sizer_pane);

	wxListItem itemCol;
	itemCol.SetText(wxT("番号"));
	threadList->InsertColumn(0, itemCol);
	itemCol.SetText(wxT("タイトル"));
	threadList->InsertColumn(1, itemCol);
	itemCol.SetText(wxT("レス"));
	threadList->InsertColumn(2, itemCol);
	itemCol.SetText(wxT("取得"));
	threadList->InsertColumn(3, itemCol);
	itemCol.SetText(wxT("新着"));
	threadList->InsertColumn(4, itemCol);
	itemCol.SetText(wxT("増レス"));
	threadList->InsertColumn(5, itemCol);
	itemCol.SetText(wxT("勢い"));
	threadList->InsertColumn(6, itemCol);
	itemCol.SetText(wxT("最終取得"));
	threadList->InsertColumn(7, itemCol);
	itemCol.SetText(wxT("since"));
	threadList->InsertColumn(8, itemCol);
	itemCol.SetText(wxT("板"));
	threadList->InsertColumn(9, itemCol);

	// データ挿入中に画面に描画すると遅くなるそうなので隠す
	threadList->Hide();

	// スレッド一覧画面を構成するデータを拾ってくる
	JaneClone::SetThreadList(outputConvPath);

	// スレッド一覧情報をリストから取ってくる
	ThreadListHash::iterator it;
	int i = 0;

	for (it = this->threadListHash.begin(); it != this->threadListHash.end();
			++it) {
		// スレッド一覧クラスの１レコード分を反映する
		ThreadList* hash = it->second;
		wxString buf;

		// 番号
		buf.Printf(wxT("%d"), i);
		long tmp = threadList->InsertItem(i, buf, 0);
		// スレタイ
		threadList->SetItem(tmp, 1, hash->title);
		// 最新のレス(スタブ)
		threadList->SetItem(tmp, 2,
				wxString::Format(wxT("%i"), hash->response));
		// 取得
		threadList->SetItem(tmp, 3,
				wxString::Format(wxT("%i"), hash->response));
		// 新着
		threadList->SetItem(tmp, 4, wxT("取得レス数"));
		// 増レス
		threadList->SetItem(tmp, 5, wxT("増レス数"));
		// 勢い
		threadList->SetItem(tmp, 6, wxT("新着レス数をここに入れる"));
		// 最終取得
		threadList->SetItem(tmp, 7, wxT("前回取得時と比べた増レス数をここに入れる"));
		// since
		threadList->SetItem(tmp, 8, wxT("計算した勢い値をここに入れる"));
		// 板名
		threadList->SetItem(tmp, 9, wxT("最終取得日を入れる"));

		// ループ変数のインクリメント
		i++;
	}
	// スレッドリストを表示させる
	threadList->Show();
}

// スレッド一覧をファイルからロードしてハッシュマップにもたせる処理
void JaneClone::SetThreadList(wxString& inputThreadListDat) {

	// テキストファイルの読み込み
	wxTextFile datfile(inputThreadListDat);
	datfile.Open();

	// スレッド一覧読み込み用正規表現を準備する
	wxRegEx reThreadLine(_T("([[:digit:]]+).dat<>(.+)\\(([[:digit:]]{1,3})\\)"),
			wxRE_ADVANCED + wxRE_ICASE);
	// スレッドに番号をつける
	int loopNumber = 1;

	// テキストファイルの終端まで読み込む
	for (wxString line = datfile.GetFirstLine(); !datfile.Eof();
			line = datfile.GetNextLine()) {

		// スレッド一覧クラスを生成する
		ThreadList *threadList = new ThreadList();

		// 正規表現で情報を取得する
		if (reThreadLine.Matches(line)) {
			// キー値を取得する
			threadList->oid = reThreadLine.GetMatch(line, 1);
			// スレタイを取得する
			threadList->title = reThreadLine.GetMatch(line, 2);
			// レス数を取得する
			threadList->response = wxAtoi(reThreadLine.GetMatch(line, 3));
		}
		// 番号
		threadList->number = loopNumber;
		// Hashにスレッド情報を入れる
		this->threadListHash[loopNumber] = threadList;
		// ループ変数をインクリメント
		loopNumber++;
	}
}

/**
 * 板一覧更新処理
 */
void JaneClone::OnGetBoardList(wxCommandEvent&) {
	// もし板一覧ファイルがdatフォルダに存在するならば一気に板一覧設定に飛ぶ
	if (wxFile::Exists(wxT("./dat/BoardListUTF8.html"))) {
		JaneClone::SetBoardList();

	// そうでなければ板一覧をダウンロードしてくる
	} else {
		JaneClone::DownloadBoardList();

		wxString inputDecommPath = wxT("./dat/BoardList.gzip");
		wxString outputDecommPath = wxT("./dat/BoardListSJIS.html");
		JaneClone::DecommpressFile(inputDecommPath, outputDecommPath);

		wxString inputConvPath = wxT("./dat/BoardListSJIS.html");
		wxString outputConvPath = wxT("./dat/BoardListUTF8.html");
		JaneClone::ConvertSJISToUTF8(inputConvPath, outputConvPath);
		JaneClone::SetBoardList();

		// 更新が終わったらgzipファイルとSJISファイルを消しておく
		if (wxFile::Exists(inputDecommPath)
				&& wxFile::Exists(outputDecommPath)) {
			wxRemoveFile(inputDecommPath);
			wxRemoveFile(outputDecommPath);
		}
	}
}

// スレッドタイトル一覧の取得メソッド
// ダウンロードしたファイルのPATHをwxStringで返却する
wxString JaneClone::DownloadThreadList(wxString& boardURL) {

	// 正規表現を使ってサーバ名と板名(ascii)を取得する
	// そこまで難しい正規表現を使う必要はないようです
	wxRegEx reThreadList(_T("(http://)([^/]+)/([^/]+)"),
			wxRE_ADVANCED + wxRE_ICASE);

	// サーバ名と板名
	wxString server;
	wxString boardName;

	// 正規表現のコンパイルにエラーがなければ
	if (reThreadList.IsValid()) {
		// マッチさせる
		if (reThreadList.Matches(boardURL)) {
			// マッチした文字列の２番目と３番目をいただく
			server = reThreadList.GetMatch(boardURL, 2);
			boardName = reThreadList.GetMatch(boardURL, 3);
		}
	}

	// ステータスバーに通信中の文字を出す
	wxString Status = boardURL;
	Status.Append(wxT("に接続中"));
	this->SetStatusText(Status);
	// HTTP通信に必要なメッセージを生成
	wxString ms = _T("/");
	ms.Append(boardName);
	wxString path = ms;
	path.Append(_T("/subjec.txt"));
	ms.Append(_T("/subjec.txt HTTP/1.1"));
	// ユーザーに見せるメッセージ
	wxString msg = "";
	// 保存先を決める
	wxString outputPath = wxT("./dat/");
	// ヘッダ用の保存先
	wxString headerPath = outputPath;
	headerPath.Append(boardName);
	headerPath.Append(wxT(".head"));

	outputPath.Append(boardName);
	outputPath.Append(wxT(".gzip"));

	// 通信のためのクラスのインスタンスを作る
	SocketCommunication* sc = new SocketCommunication();
	sc->DownloadThreadList(boardURL, server, boardName, outputPath, headerPath);
	delete sc;

	// ステータスバーに通信終了の文字を出す
	Status.Clear();
	Status = boardURL;
	Status.Append(wxT("からのダウンロード終了"));
	this->SetStatusText(Status);

	// 戻り値は出力したgzipファイルの保存先
	return outputPath;
}

// 板一覧ファイルをダウンロードする処理
void JaneClone::DownloadBoardList() {

	// ここから
	wxHTTP http;
	http.SetHeader(_T("Accept-Encoding"), _T("gzip"));
	http.SetHeader(_T("Host"), _T("menu.2ch.net"));
	http.SetHeader(_T("Accept"), _T(""));
	http.SetHeader(_T("Referer"), _T("http://menu.2ch.net/"));
	http.SetHeader(_T("Accept-Language"), _T("ja"));
	http.SetHeader(_T("User-Agent"), _T("Mozilla/5.0"));
	http.SetTimeout(5);

	wxString server = "menu.2ch.net";
	wxString path = "/bbsmenu.html";
	wxString msg = "";

	// 保存先を決める
	wxFileOutputStream output(wxT("./dat/BoardList.gzip"));
	wxDataOutputStream store(output);

	if (http.Connect(server, 80)) {
		msg = wxT("接続しました");
		wxInputStream *stream;
		stream = http.GetInputStream(path);

		if (stream == NULL) {
			msg = wxT("サーバと通信できませんでした");
		} else {
			unsigned char buffer[1024];
			int byteRead;
			int totalRead;
			totalRead = 0;

			while (!stream->Eof()) {
				stream->Read(buffer, sizeof(buffer));
				store.Write8(buffer, sizeof(buffer));
				byteRead = stream->LastRead();
				if (byteRead <= 0) {
					break;
				}
				totalRead += byteRead;
			}
			msg = wxT("板一覧更新処理を終了しました");
		}
	} else {
		msg = wxT("サーバーに接続できませんでした");
	}
	wxMessageBox(msg);
}

/**
 * DecommpressFile()
 * gzipファイルを解凍する処理
 * 引数１は読み込み元gzipファイルのPATH、引数２は解凍先のファイルのPATH
 * いずれもファイル名までを記述する
 */
void JaneClone::DecommpressFile(wxString& inputPath, wxString& outputPath) {
	// gzファイルをZlibを使って解凍する
	gzFile infile = gzopen(inputPath.mb_str(), "rb");
	FILE *outfile = fopen(outputPath.mb_str(), "wb");

	char buffer[S_SIZE];
	int num_read = 0;
	while ((num_read = gzread(infile, buffer, sizeof(buffer))) > 0) {
		fwrite(buffer, 1, num_read, outfile);
	}

	// ファイルポインタを閉じる
	gzclose(infile);
	fclose(outfile);
}

/**
 * ConvertSJISToUTF8()
 * ダウンロードしたファイルの文字コードをShift-JISからUTF-8に変換する処理
 * 引数１は読み込み元のPATH、引数２は出力先ファイルのPATH
 * いずれもファイル名までを記述する
 */
void JaneClone::ConvertSJISToUTF8(wxString& inputPath, wxString& outputPath) {

	iconv_t icd;
	FILE *fp_src, *fp_dst;
	char s_src[S_SIZE], s_dst[D_SIZE];
	char *p_src;
	char *p_dst;
	size_t n_src, n_dst;
	int* iconctl;

	// 文字コード変換はCP932からUTF-8
	icd = iconv_open("UTF-8", "CP932");
	//  iconvctl で変換不可能な文字があった時の設定
	//  変換不可能だったら捨てる
	//  不正な文字があり、捨てられたときは iconctlに1が入る
	iconvctl(icd, ICONV_GET_DISCARD_ILSEQ, iconctl);

	fp_src = fopen(inputPath.mb_str(), "r");
	fp_dst = fopen(outputPath.mb_str(), "w");

	while (true) {
		fgets(s_src, S_SIZE, fp_src);
		if (feof(fp_src))
			break;
		p_src = s_src;
		p_dst = s_dst;
		n_src = strlen(s_src);
		n_dst = S_SIZE - 1;
		while (0 < n_src) {
			size_t result;
			result = iconv(icd, &p_src, &n_src, &p_dst, &n_dst);
			// エラーがあれば止める
			if (result == -1) {
				this->SetStatusText(wxT("文字コード変換でエラーがありました。"));
				perror("iconv");
				break;
			}
		}
		*p_dst = '\0';
		fputs(s_dst, fp_dst);
	}
	this->SetStatusText(wxT("文字コード変換終了"));
	fclose(fp_dst);
	fclose(fp_src);
	iconv_close(icd);
}

/**
 * 取得した板一覧ファイルからデータを抽出してレイアウトに反映するメソッド
 */
void JaneClone::SetBoardList() {

	// インスタンスを作る
	ExtractBoardList *extractBoardList = new ExtractBoardList();
	delete extractBoardList;

	/** 全面的な書き直し　・・・　SQLiteに板情報を格納・そこからHashに情報格納
	// 板一覧の情報が入ったリストをもらう
	wxArrayString boardListArray = ebl->GetBoardList();
	// フラグ
	boolean category_flag = false;
	// カテゴリ名一時格納用
	wxString categoryName;
	// カテゴリ名のプレフィックス
	wxString c_prefix = wxT("c::");
	// カテゴリ名を保持するためのID
	wxTreeItemId category;
	// 板名とURLを対応させるHashを生成しておく
	NameURLHash tmpHash;
	// Hashのカウント用Integer
	int hashID = 0;

	// GUIにツリーコントロールを反映する
	// 2chの入り口, 2ch総合案内を除外しているのでループ変数は5から始まる
	// あと最後の方の余分なURLも除外している。 -- サーバに変更があった場合困るなあ…
	for (int i = 5; i < boardListArray.GetCount() - 2; i++) {
		// 文字列が入っていなければツリーには入れない
		if (!boardListArray[i].IsSameAs("")) {
			// カテゴリフォルダだったらフラグ立てる
			if (boardListArray[i].Contains(c_prefix)) {
				category_flag = true;
				categoryName = boardListArray[i].Remove(0, 3);
			}
			// カテゴリフォルダに当たる場合フォルダアイコンとしてツリーに登録
			if (category_flag) {
				category = m_tree_ctrl->AppendItem(m_rootId, categoryName, 0, 0,
						m_treeData);
				category_flag = false;
			} else {
				// もしhttp://~　を含んでいればURLとみなして飛ばす、そうでないならツリーに情報を追加
				if (!boardListArray[i].Contains(wxT("http://"))) {
					// ツリーに板名かURLを追加する
					m_tree_ctrl->AppendItem(category, boardListArray[i], 1, 1,
							m_treeData);
					// ここの辺のコードが汚すぎて死ぬ
					// 板名の配列に板名とURLを入れておく
					URLvsBoardName* urlVsName = new URLvsBoardName;
					urlVsName->BoardName = boardListArray[i];
					urlVsName->BoardURL = boardListArray[i + 1];

					// 正規表現を使ってサーバ名と板名(ascii)を取得する
					// そこまで難しい正規表現を使う必要はないようです
					wxRegEx reThreadList(_T("(http://)([^/]+)/([^/]+)"),
							wxRE_ADVANCED + wxRE_ICASE);

					// 正規表現のコンパイルにエラーがなければ
					if (reThreadList.IsValid()) {
						// マッチさせる
						if (reThreadList.Matches(boardListArray[i + 1])) {
							// マッチした文字列の３番目をいただく
							urlVsName->BoardNameAscii = reThreadList.GetMatch(
									boardListArray[i + 1], 3);
						}
					}
					// Hashに板情報を入れる
					tmpHash[hashID] = urlVsName;
					// Hashのキー値をインクリメントしておく
					hashID++;
				}
			}
		}
	}
	this->retainHash = tmpHash;

	*/
}

// GUI上で右クリックされた際に起こるイベント処理
void JaneClone::OnContext(wxContextMenuEvent& event) {
	wxMessageBox(wxT("右クリックしましたねm9( ﾟдﾟ)"));
}

void JaneClone::OnRightClick(wxAuiNotebookEvent& event) {
	wxMessageBox(wxT("右クリックしましたねm9( ﾟдﾟ)"));
}

// バージョン情報が書かれたダイアログを表示する処理
void JaneClone::OnVersionInfo(wxCommandEvent&) {
	wxAboutDialogInfo info;
	info.SetName(wxT("Jane Clone - ２ちゃんねるビューア"));
	info.SetVersion(wxT("0.0.8"));
	info.SetDescription(wxT("Copyright(C) 2011 Nantonaku-Shiawase"));
	info.SetCopyright(wxT("http://d.hatena.ne.jp/panzer-jagdironscrap1/"));

	wxAboutBox(info);
}

// 終了前処理では、保存しておきたいユーザー設定をSQLiteに登録しておく
void JaneClone::OnCloseWindow(wxCloseEvent& event) {

	// JaneClone終了時ユーザがノートブック部分に残していた板名のリストを作る
	//wxArrayString userLookBoard;
	//for (int i=0;i < boardNoteBook->GetPageCount();i++) {
	//	userLookBoard.Add(boardNoteBook->GetPageText(i));
	//}

	// ユーザが開いていた板一覧をSQLiteに登録する
	//if ( 0 != userLookBoard.GetCount() ) {
		//SQLiteBundle* sqlite = new SQLiteBundle();
		//int rc = sqlite->UserLookingBoardRegister(userLookBoard);
		//delete sqlite;

		// 実行コードがエラーならば警告を出して終了
		//if (rc != 0) {
		//	wxMessageBox(wxT("終了処理にてエラーが発生しました"));
		//	Destroy();
		//}
	//}

	// ウィンドウを閉じて処理を終了される
	Destroy();
}
