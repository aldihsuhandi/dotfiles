" $HOME/.config/nvim/init.vim

" General Shortcut
map <F1> :NERDTreeToggle<CR>
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

" Compiling Shortcut
map <F5> :w! <bar> :term ~/Documents/vim\ script/./compile.sh %<CR>
map <F8> :w! <bar> :term echo "Insert to IN" && cat > in<CR>
map <F9> :w! <bar> :term ~/Documents/vim\ script/./run.sh %<CR>
map <F10> :w! <bar> :term ~/Documents/vim\ script/./compile.sh % && time ./%:r < in<CR>
nnoremap <F11> :wall! <bar> :term javac Main.java && java Main<CR>

" Comment shortcut
vmap  <plug>NERDCommenterToggle
nmap  <plug>NERDCommenterToggle

" Automatically closing braces
inoremap {<CR> {<CR>}<Esc>ko

" Files searching
map <C-P> :Files<CR>

" Navigate Between Tab
nnoremap <C-Down> :tabNext<CR>
nnoremap <C-Up> :tabprevious<CR>

" Navigate Between Buffer
nnoremap <C-L> :bn<CR>
nnoremap <C-H> :bp<CR>
