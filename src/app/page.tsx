import Link from "next/link";

const features = [
  {
    title: "Context-Aware Tagging",
    description:
      "Batch apply gameplay tags to every selected actor using flexible CSV input and optional overrides.",
  },
  {
    title: "Metadata Stamping",
    description:
      "Persist production metadata as tag pairs so level designers and technical artists stay in sync.",
  },
  {
    title: "Smart Renaming",
    description:
      "Generate clean, human-readable labels with tokenised patterns like {BaseName} and {Index}.",
  },
];

const workflow = [
  "Drop the SmartTagger folder inside your Unreal project's Plugins directory.",
  "Enable the plugin in Edit → Plugins and restart the editor.",
  "Select any actors in the level viewport and hit the Smart Tagger toolbar button.",
  "Fill in tags, metadata, and rename patterns, then confirm to apply instant clean-up.",
];

export default function Home() {
  return (
    <div className="min-h-screen bg-neutral-950 text-neutral-100">
      <main className="mx-auto flex w-full max-w-6xl flex-col gap-24 px-6 pb-32 pt-24 sm:px-12">
        <section className="grid gap-16 lg:grid-cols-[1.1fr_0.9fr] lg:items-center">
          <div className="space-y-6">
            <p className="inline-flex items-center rounded-full bg-emerald-500/10 px-4 py-1 text-sm font-semibold text-emerald-300">
              Unreal Engine Editor Utility
            </p>
            <h1 className="text-4xl font-semibold leading-tight sm:text-5xl lg:text-6xl">
              Smart&nbsp;Tagger — automate actor tagging, metadata, and naming in
              one pass.
            </h1>
            <p className="max-w-2xl text-lg text-neutral-300">
              Ship rock-solid level organisation in seconds. Smart Tagger batches
              gameplay tags, metadata, and naming patterns from a single editor
              window so designers, TDs, and QA stay aligned across large worlds.
            </p>
            <div className="flex flex-col gap-4 sm:flex-row">
              <Link
                href="/downloads/SmartTaggerPlugin.zip"
                className="flex items-center justify-center rounded-lg bg-emerald-500 px-6 py-3 text-base font-semibold text-neutral-900 transition hover:bg-emerald-400"
              >
                Download Plugin
              </Link>
              <a
                href="#workflow"
                className="flex items-center justify-center rounded-lg border border-neutral-700 px-6 py-3 text-base font-semibold transition hover:border-neutral-500"
              >
                View Workflow
              </a>
            </div>
          </div>
          <div className="relative overflow-hidden rounded-2xl border border-neutral-800 bg-neutral-900/60 p-6 shadow-lg">
            <div className="absolute inset-0 -z-10 bg-gradient-to-br from-emerald-500/10 via-transparent to-cyan-500/10" />
            <div className="flex items-center justify-between text-sm text-neutral-400">
              <span>SmartTagger.uplugin</span>
              <span>Editor Module</span>
            </div>
            <pre className="mt-6 overflow-x-auto rounded-xl bg-neutral-950/60 p-5 text-xs leading-relaxed text-emerald-100">
              <code>
{`{
  "FriendlyName": "Smart Tagger",
  "Description": "Editor utility plugin that applies gameplay tags, metadata, and naming schemes to selected actors.",
  "Modules": [
    {
      "Name": "SmartTagger",
      "Type": "Editor",
      "LoadingPhase": "PostEngineInit"
    }
  ]
}`}
              </code>
            </pre>
          </div>
        </section>

        <section className="grid gap-10 lg:grid-cols-3">
          {features.map((feature) => (
            <article
              key={feature.title}
              className="flex flex-col gap-4 rounded-xl border border-neutral-800 bg-neutral-900/60 p-6"
            >
              <h2 className="text-xl font-semibold text-white">{feature.title}</h2>
              <p className="text-neutral-300">{feature.description}</p>
            </article>
          ))}
        </section>

        <section
          id="workflow"
          className="grid gap-12 rounded-3xl border border-neutral-800 bg-neutral-900/80 p-10 md:grid-cols-[1.1fr]"
        >
          <div className="space-y-4">
            <h2 className="text-3xl font-semibold text-white">
              Quick install checklist
            </h2>
            <p className="max-w-2xl text-neutral-300">
              The download ships with full C++ source, Slate UI, and icon assets.
              Keep the folder name SmartTagger when copying into your project.
            </p>
          </div>
          <ol className="space-y-4 text-neutral-200">
            {workflow.map((step, index) => (
              <li key={index} className="flex gap-4">
                <span className="flex h-8 w-8 items-center justify-center rounded-full bg-emerald-500/20 text-sm font-semibold text-emerald-300">
                  {index + 1}
                </span>
                <span className="text-base leading-relaxed">{step}</span>
              </li>
            ))}
          </ol>
        </section>

        <section className="grid gap-8 md:grid-cols-[0.65fr_0.35fr]">
          <div className="rounded-3xl border border-neutral-800 bg-neutral-900/70 p-8">
            <h3 className="text-2xl font-semibold text-white">
              Blueprint helper library
            </h3>
            <p className="mt-3 text-neutral-300">
              Smart Tagger ships with an optional Blueprint function library so
              automated pipelines can tag assets during cook or validation.
              Functions are namespaced under{" "}
              <code className="rounded bg-neutral-800 px-2 py-1 text-sm text-emerald-200">
                SmartTagger
              </code>{" "}
              for easy discovery.
            </p>
            <pre className="mt-6 overflow-x-auto rounded-2xl bg-neutral-950/60 p-5 text-xs leading-relaxed text-emerald-100">
              <code>
{`UFUNCTION(BlueprintCallable, CallInEditor)
static void SmartApplyTags(const TArray<AActor*>& Actors,
                           const TArray<FName>& Tags,
                           bool bAppend);`}
              </code>
            </pre>
          </div>
          <div className="flex flex-col justify-between gap-6 rounded-3xl border border-neutral-800 bg-neutral-900/70 p-8">
            <div>
              <h3 className="text-2xl font-semibold text-white">Need tweaks?</h3>
              <p className="mt-3 text-neutral-300">
                Extend the module with additional Slate widgets, register asset
                automation commands, or wire the library into Control Rig or
                Sequencer workflows.
              </p>
            </div>
            <Link
              href="/downloads/SmartTaggerPlugin.zip"
              className="inline-flex items-center justify-center rounded-lg border border-emerald-400/80 px-4 py-2 text-sm font-semibold text-emerald-200 transition hover:bg-emerald-500/10"
            >
              Grab the source again
            </Link>
          </div>
        </section>
      </main>
    </div>
  );
}
