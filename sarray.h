//必要最低限の機能を備えた文字列クラス。
//## 機能
//- バッファサイズを自動的に拡張する。
//- アロケート・解放・長さ・格納・連結・シュリンク・複製

//文字のデータ型
typedef char sarray_char_t;

//文字列クラス
typedef struct {
    size_t capacity;
    sarray_char_t *str_buf;
} sarray_t;

//アレイをアロケートする。
//init_capacityには初期最大データサイズを指定する。0の場合はデフォルト値が使用される。
//長さ(array->num)は常に0となる。
sarray_t *new_sarray(const sarray_char_t *str);

//アレイを解放する。
void free_sarray(sarray_t *sarray);

//アレイの長さ（文字列の長さ）を取得する。
size_t len_sarray(const sarray_t *sarray);

//アレイに指定された文字列を格納し、格納された文字列のポインタを返す。
//アレイの長さは指定された文字列を格納するのに十分なサイズに自動的に拡張される。
sarray_char_t *set_sarray(sarray_t *sarray, const sarray_char_t *str);

//アレイの最後に文字列を連結（追加）し、格納された文字列のポインタを返す。
//アレイの長さは指定された文字列を格納するのに十分なサイズに自動的に拡張される。
sarray_char_t *concat_sarray(sarray_t *sarray, const sarray_char_t *str);

//アレイのサイズを必要最低限にシュリンクし、格納された文字列のポインタを返す。
sarray_char_t *shrink_sarray(sarray_t *sarray);

//アレイを複製する。
//複製されたアレイの内部データは必要最低限分が確保される。
#define dup_sarray(sarray) new_sarray((sarray)->str_buf)
