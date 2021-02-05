local tek = require "@nasso/epine-tek/v0.1.0-alpha6"

tek:project "libgote" {"libgote.a"}

tek:static "libgote" {
    libs = {tek:ref "libmy"}
}

tek:binary "unit_tests" {
    srcs = {find "./tests/*.c"},
    libs = {tek:ref "libgote", tek:ref "libmy", "criterion"}
}

tek:pull "libmy" {git = "git@github.com:nasso/libmy"}

return tek:make()
