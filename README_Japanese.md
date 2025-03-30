# cppScheduler

## 概要
SchedulerProjectは、ファイルデータを自動処理し、データベースに保存するプログラムです。  
TXTおよびCSVファイルを読み込み、データを処理してMySQLデータベースに記録し、毎日深夜0時に自動実行されます。

---

## 開発環境
```
C++17
MySQL
dotenvライブラリ
Visual Studio Code(VS Code)
```

## プロジェクト構造

```
cppScheduler/
├── src/                 # ソースコード (.cppファイル)  
│   ├── FileProcessor.cpp  
│   ├── RecordMapper.cpp  
│   ├── RecordUtil.cpp  
│   ├── Scheduler.cpp  
│   ├── SchedulerService.cpp  
├── include/             # ヘッダファイル (.hファイル)  
│   ├── ConstVO.h  
│   ├── FileProcessor.h  
│   ├── RecordMapper.h  
│   ├── RecordUtil.h  
│   ├── Scheduler.h  
│   ├── SchedulerService.h  
├── config/              # 設定ファイル  
│   ├── .env  
│   ├── queries.dat  
├── scripts/             # 実行スクリプト  
│   ├── SchedulerScript.ksh  
├── logs/                # ログファイル保存場所 (実行時に生成)  
```

---

## インストール方法

### 1. ソースコードをクローン
```bash
git clone https://github.com/kwanmo7/cppScheduler.git
cd cppScheduler
```

### 2. MySQLおよびdotenvライブラリをインストール
MySQLクライアントをインストールし、dotenvライブラリを導入します。

### 3. CMakeビルド
```bash
mkdir build
cd build
cmake ..
make
```

---

## 実行方法

### 1. 環境変数の設定
`config/.env` ファイルでデータベース接続に必要な環境変数を設定します。

```bash
DB_URL=database-url
DB_USER=database-user
DB_PASSWORD=database-password
```

### 2. クエリファイルの設定
`config/queries.dat` ファイルにSQLクエリを定義します。

### 3. スケジューラースクリプトの実行
```bash
chmod +x scripts/SchedulerScript.ksh
./scripts/SchedulerScript.ksh
```

---

## クーロンジョブの自動化

### 1. `crontab -e` を実行してクーロンジョブを編集します。
### 2. 以下の行を追加し、毎日深夜0時に実行されるよう設定します。
```bash
0 0 * * * /path/to/scripts/SchedulerScript.ksh
```
### 3. ログファイルは `logs/scheduler.log` に記録されます。

---

## ログの確認
実行ログは `logs/scheduler.log` ファイルに保存されます。リアルタイムでログを確認するには、以下のコマンドを実行してください。

```bash
tail -f logs/scheduler.log
```

