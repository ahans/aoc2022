def _day01_repo_impl(ctx):
    elves = []
    for line in ctx.read(ctx.attr.src).split("\n\n"):
        nums = [x for x in line.split("\n")]
        s = 0
        for n in nums:
            if len(n) > 1:
                s += int(n)
        elves.append(s)
    elves = sorted(elves)
    ctx.file("dump.sh", content = """
    echo "Part #1: {}"
    echo "Part #2: {}"
""".format(elves[-1], elves[-1] + elves[-2] + elves[-3]), executable = True)
    ctx.file("BUILD.bazel", content = """
sh_binary(
    name = "solve",
    srcs = ["dump.sh"],
)
""")

day01_repo = repository_rule(
    implementation = _day01_repo_impl,
    attrs = {
        "src": attr.label(),
    },
)
