" Enable trimmming of trailing whitespace
let g:neoformat_basic_format_trim = 1

" Run formatter on save
augroup fmt
    autocmd!
    autocmd BufWritePre * undojoin | Neoformat
augroup END
