" General Shortcut
map <F1> :NvimTreeToggle<CR>
nnoremap <C-h> <C-w>h
nnoremap <C-j> <C-w>j
nnoremap <C-k> <C-w>k
nnoremap <C-l> <C-w>l
nnoremap <C-c> :%y+<CR>
nnoremap <C-w> :wall<CR>
nnoremap <C-q> :so ~/.config/nvim/init.vim<CR>
noremap <silent> <A-Left> :vertical resize +3<CR>
noremap <silent> <A-Right> :vertical resize -3<CR>
noremap <silent> <A-Up> :resize +3<CR>
noremap <silent> <A-Down> :resize -3<CR>

" file search
map <C-P> :FzfLua files<CR>
map <C-S-P> :FzfLua grep_project<CR>
