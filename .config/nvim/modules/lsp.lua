local registries = {
	"github:nvim-java/mason-registry",
	"github:mason-org/mason-registry"
}
require("mason").setup(
{
  	registries = registries,
  	ui = {
    	    	icons = {
      		    	package_installed = "✓",
      		    	package_pending = "➜",
      		    	package_uninstalled = "✗",
    	    	},
    	},
})


require("java").setup()
require("lspconfig").jdtls.setup({
    "lombok"
})
