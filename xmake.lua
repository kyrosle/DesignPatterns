add_rules("mode.debug", "mode.release")

--- main
target("main")
  set_kind("binary")
  add_files("src/*.cpp")

projects = {
  "abstract_factory",
  "adapter",
  "bridge",
  "composite",
  "decorator",
  "facade",
  "factory_method",
  "prototype",
  "singleton",
  "flyweight",
  "proxy",
  "chain",
  "command",
  "iterator",
  "mediator",
  "memento",
  "observer",
  "state",
  "strategy",
  "template",
  "visitor"
}

function solve(project_name)
  target(project_name)
    set_kind("binary")
    add_files(string.format("lib/%s/*.cpp", project_name))
end

for _, value in ipairs(projects) do
  solve(value)
end

