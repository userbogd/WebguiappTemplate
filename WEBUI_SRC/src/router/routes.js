const routes = [
  {
    path: "/",
    component: () => import("layouts/MainLayout.vue"),
    children: [
      { path: "", component: () => import("pages/HomePage.vue") },
      { path: "home", component: () => import("pages/HomePage.vue") },
      { path: "appset", component: () => import("pages/AppSettingsPage.vue") },
      { path: "ifsettings", component: () => import("pages/InterfacesSettings.vue") },
      { path: "services", component: () => import("pages/ServicesPage.vue") },
      { path: "system", component: () => import("pages/SystemPage.vue") },
      { path: "storage", component: () => import("pages/StoragePage.vue") },
    ],
  },

  // Always leave this as last one,
  // but you can also remove it
  {
    path: "/:catchAll(.*)*",
    component: () => import("pages/ErrorNotFound.vue"),
  },
];

export default routes;
