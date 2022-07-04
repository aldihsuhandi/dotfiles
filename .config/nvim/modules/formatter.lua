vim.api.nvim_exec([[
augroup FormatAutogroup
  autocmd!
  autocmd BufWritePost *.js,*.rs,*.lua,*.cpp,*.c FormatWrite
augroup END
]], true)


-- require('formatter').setup({
--   filetype = {
--     cpp = {
--         -- clang-format
--        function()
--           return {
--             exe = "astyle",
--             args = {"--assume-filename", vim.api.nvim_buf_get_name(0)},
--             stdin = true,
--             cwd = vim.fn.expand('%:p:h')  -- Run clang-format in cwd of the file.
--           }
--         end
--     },
--   }
-- })
