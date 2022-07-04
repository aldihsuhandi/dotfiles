" Enable trimmming of trailing whitespace
let g:neoformat_basic_format_trim = 1

" neoformat c anc cpp use astyle
" let g:neoformat_enabled_cpp = ['astyle']
" let g:neoformat_enabled_c = ['astyle']

" Run formatter on save
augroup fmt
    autocmd!
    autocmd BufWritePre * undojoin | Neoformat
augroup END
